# Jogo black jack desenvolvido numa rede em anel, disciplina redes1
# Bruno Vila Lobus Strapasson - GRR20215522
# Vinicius de Paula - GRR20190360

import pickle 
import sys


class Packet:
    def __init__(self, sender, message_type, message, verifier=False):
        self.sender = sender  # Quem envia a mensagem
        self.message_type = message_type  # Tipo da mensagem
        self.message = message  # Mensagem
        self.verifier = verifier  # Verificador de recebimento

    def __str__(self):
        return f"Sender: {self.sender}, Type: {self.message_type}, Message: {self.message}, Verifier: {self.verifier}"

class BroadcastPacket(Packet): 
    def __init__(self, sender, message_type, message, verifier=[False, False, False, False]):
        super().__init__(sender, message_type, message, verifier)

    def __str__(self):
        return f"Broadcast -> {super().__str__()}"

class UnicastPacket(Packet):
    def __init__(self, sender, dest, message_type, message, verifier=False):
        super().__init__(sender, message_type, message, verifier)
        self.dest = dest  # Para quem a mensagem está sendo enviada

    def __str__(self):
        return f"Unicast -> {super().__str__()}, Dest: {self.dest}"

# DINF
#NETWORK_ADDRESSES = [
#    (("10.254.224.56", 21254), 0), # 0 
#    (("10.254.224.57", 21255), 1), # 1 
#    (("10.254.224.58", 21256), 2), # 2 
#    (("10.254.224.59", 21257), 3)  # 3
#]

# Local
NETWORK_ADDRESSES = [
     (("127.0.0.1", 21254), 0), # 0
     (("127.0.0.1", 21255), 1), # 1
     (("127.0.0.1", 21256), 2), # 2 
     (("127.0.0.1", 21257), 3)  # 3
 ]

# Configura os endereços de rede com base no argumento passado
def get_addresses():
    identification = int(sys.argv[1])
    return NETWORK_ADDRESSES[identification], NETWORK_ADDRESSES[(identification + 1) % 4]

# Verifica se a mensagem foi recebida corretamente 
def verifications(type_message, sender_index, socket_receiver):
    if type_message == "TOKEN": # TOKEN
        data, _ = socket_receiver.recvfrom(1024)
        packet = pickle.loads(data)
        if packet.sender ==  sender_index and packet.verifier == True:
            return True, packet.message
        return False, None
    # Se for um broadcast
    data, _ = socket_receiver.recvfrom(1024)
    packet = pickle.loads(data)
    if packet.sender == sender_index:
        for i in range(4):
            if i == sender_index:
                continue
            if packet.verifier[i] == False:
                return False, None 
        return True, packet.message
    
def send_player_action(socket_sender, action, player_index, NEXT_NODE_ADDRESS):
    message = {
        "type": "PLAYER-ACTION",
        "player": player_index,
        "action": action,
    }
    send_unicast(socket_sender, None, "ACTION", message, player_index, NEXT_NODE_ADDRESS)

# Envia a mensagem de broadcast
def send_broadcast(socket_sender, socket_receiver, type_message, message, sender_index, NEXT_NODE_ADDRESS):
    packet = BroadcastPacket(sender_index, type_message, message)
    socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
    # Verifica se a mensagem foi recebida corretamente e reenvia caso não tenha sido
    validation, message = verifications(type_message, sender_index, socket_receiver)
    while validation == False:
        validation, message = verifications(type_message, sender_index, socket_receiver)
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
    return message

# Envia a mensagem de unicast
def send_unicast(socket_sender, socket_receiver, type_message, message, sender_index, NEXT_NODE_ADDRESS):
    packet = UnicastPacket(sender_index, message[0] , "TOKEN", message[1])
    socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
    # Verifica se a mensagem foi recebida corretamente e reenvia caso não tenha sido
    validation, message = verifications(type_message, sender_index, socket_receiver)
    while validation == False:
        validation, message = verifications(type_message, sender_index, socket_receiver)
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
    return message 

# Verifica se os jogadores anteriores receberam a mensagem
def verify_verifiers(packet, node_index):
    n_trues = 0
    if packet.sender == 0:
        if node_index == 1:
            n_trues = 0
        elif node_index == 2:
            n_trues = 1
        elif node_index == 3:
            n_trues = 2
    elif packet.sender == 1:
        if node_index == 2:
            n_trues = 0
        elif node_index == 3:
            n_trues = 1
        elif node_index == 0:
            n_trues = 2
    elif packet.sender == 2:
        if node_index == 3:
            n_trues = 0
        elif node_index == 0:
            n_trues = 1
        elif node_index == 1:
            n_trues = 2
    elif packet.sender == 3:
        if node_index == 0:
            n_trues = 0
        elif node_index == 1:
            n_trues = 1
        elif node_index == 2:
            n_trues = 2

    if n_trues == 0:
        return True
    else:
        if packet.verifier.count(True) == n_trues:
            return True
        else:
            return False

# Filtra as mensagens recebidas nas redes pelos nós que não estão com o bastão
def ring_messages(CURRENT_NODE_ADDRESS, NEXT_NODE_ADDRESS, game, socket_receiver, socket_sender, player):
    data, _ = socket_receiver.recvfrom(1024)
    packet = pickle.loads(data)

    # Tratamento das mensagens de unicast:   
    if packet.message_type == "TOKEN": # TOKEN 
        if packet.dest == CURRENT_NODE_ADDRESS[1]:
            packet.verifier = True # não é um vetor pq é unicast
            socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
            # time.sleep(1) # Garante que a mensagem de token recebido chegou no jogador que enviou
            game.set_state(packet.message) # Atualiza o estado do jogo
            return 1 # RETORNA QUE O TOKEN FOI RECEBIDO
        else: # Se não for para mim, passo adiante
            socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
            return 2 # Continua o funcionamento da rede
    
    # Tratamento das mensagens de broadcast:
    # Se algum nodo anterior não verificou a mensagem, reenvia até o nodo com o bastão para ele reenviar a mensagem
    if verify_verifiers(packet, CURRENT_NODE_ADDRESS[1]) == False:
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Recebe o estado do jogo
    # Ação do jogador
    elif packet.message_type == "PLAYER-ACTION":
        if packet.verifier[player.index]:
            return 2  # Já processado
        action = player.player_action(game)  # Jogador escolhe "hit" ou "stand"
        game.set_points_played(packet.message, action, player.index)
        packet.message[player.index] = game.get_points_played()
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2
    # Ação do dealer
    elif packet.message_type == "DEALER-ACTION":
        if packet.verifier[player.index]:
            return 2  # Já processado
        if player.index == game.state["dealer"]:  # O dealer joga
            #game.dealer_play()
            packet.message = game.get_dealer_hand()
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2
    # estado do jgo
    elif packet.message_type == "GAME-STATE":
        game.set_state(packet.message)
        if game.state["players_alive"][player.index] == True:
            print(f"\nROUND : {game.state['round']}\n")
            #player.set_vira(packet.message['vira'])
        else:
            print(f"Você foi eliminado ...")
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # CARTAS enviadas pelo dealer
    elif packet.message_type == "CARDS": 
        #print(f"player.index: {player.index}")
        player.set_cards(packet.message[player.index])
        packet.verifier[player.index] = True # Marca que a mensagem foi recebida
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Recolhe o palpite do player e mostra os anteriores
    elif packet.message_type == "TAKE-GUESSES":
        player.make_a_guess(game, packet.message)
        packet.message[player.index] = player.guess
        packet.verifier[player.index] = True # Marca que a mensagem foi recebida
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Mostra todos os palpites feitos
    elif packet.message_type == "SHOW-PONTOS":
        player.show_points(packet.message)
        packet.verifier[player.index] = True # Marca que a mensagem foi recebida
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Jogador joga uma carta na sub rodada
    elif packet.message_type == "PLAY-CARD":
        player.play_a_card(packet.message)
        game.set_card_played(packet.message, player.card_played, player.index)
        packet.message = game.get_cards_played()
        packet.verifier[player.index] = True # Marca que a mensagem foi recebida
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Mostra as cartas jogadas
    elif packet.message_type == "SHOW-CARDS":
        player.show_points(packet.message)
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    elif packet.message_type == "CONTABILIZE":
        player.retorna_guess(packet.message)
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    # Mostra quem fez a sub rodada
    elif packet.message_type == "SUBROUND-WINNER":
        player.sub_round_winner(packet.message)
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
    # Recebe as informações sobre o fim da rodada
    elif packet.message_type == "CASH-AVAL":
        cash = player.get_cash()
        if cash == 0:
            player.set_lifes(player.index)
        packet.verifier[player.index] = True # Marca que a mensagem foi recebida
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        return 2 # Continua o funcionamento da rede
    elif packet.message_type == "END-CONNECTION":
        if packet.verifier[player.index]:
            return 2  # Já processado
        print("Recebida mensagem de encerramento. Fechando conexão...")
        packet.verifier[player.index] = True
        socket_sender.sendto(pickle.dumps(packet), NEXT_NODE_ADDRESS[0])
        socket_receiver.close()
        sys.exit()
        return 2  # Finaliza o jogo