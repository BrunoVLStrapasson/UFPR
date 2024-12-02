from network import send_broadcast, send_unicast

class Player:
    def __init__(self, index):
        self.lifes = 1
        self.cards = []
        #self.vira = None
        self.guess = None
        self.index = index
        #self.card_played = None

# class Player:
#     def __init__(self, index):
#         self.lifes = 3
#         self.cards = []
#         self.vira = None
#         self.guess = None
#         self.index = index
#         self.card_played = None
    
    # Métodos set

    def set_lifes(self, lifes):
        self.lifes = lifes

    def set_cards(self, cards):
        self.cards = cards  # Define as cartas do jogador

#    def set_vira(self, vira):
#        print(f"Vira recebido: {vira}")
#        self.vira = vira
#        # Manilha
#        if self.vira[0] == '7':
#            print("Manilha da rodada: Q (Dama)")
#        elif self.vira[0] == 'Q (Dama)':
#            print("Manilha da rodada: J (Valete)")
#        elif self.vira[0] == 'J (Valete)':
#            print("Manilha da rodada: K (Rei)")
#        elif self.vira[0] == 'K (Rei)':
#            print("Manilha da rodada: A")
#        elif self.vira[0] == 'A':
#            print("Manilha da rodada: 2")
#        else:
#            print(f"Manilha da rodada: {int(self.vira[0])+1}")    

    def set_guess(self, guess):
        self.guess = guess

    def set_index(self, index):
        self.index = index

#    def set_card_played(self, card_played):
#        self.card_played = card_played

    # Métodos get
    def get_lifes(self):
        return self.lifes

    def get_cards(self):
        return self.cards

#    def get_vira(self):
#        return self.vira

    def get_guess(self):
        return self.guess

    def get_index(self):
        return self.index

#    def get_card_played(self):
#        return self.card_played
    
#    def sub_round_winner(self, winner):
#        if winner == self.index:
#            print("Você venceu a sub-rodada!")
#        else:    
#            print(f"O jogador {winner} venceu a sub-rodada!")
 
    # Mostra todas as cartas jogadas na sub-rodada
    def show_cards(self, cards):
        print("Cartas jogadas: ")
        for i in range(4):
            if cards[i] is not None:
                print(f"Jogador {i}: {cards[i][0]} de {cards[i][1]}")
    
#    # Mostra todos os palpites feitos
#    def show_guesses(self, guesses):
#        print("Palpites: ")
#        for i in range(4):
#            if guesses[i] is not None:
#                print(f"Jogador {i}: {guesses[i]}")

#    # Faz um palpite e guarda no objeto 
#    def make_a_guess(self, game, previous_guesses):
#        sum_guesses = 0
#        n_previous_guesses = len([guess for guess in previous_guesses if guess is not None])
#        # Primeiro palpite da rodada
#        if n_previous_guesses == 0: 
#            while True:
#                try:
#                    guess = int(input("Digite seu palpite: "))
#                    if 0 <= guess <= game.get_round():
#                        self.guess = guess
#                        return self.guess
#                    else:
#                        print(f"Por favor, digite um número entre 0 e {game.get_round():}.")
#                except ValueError:
#                    print("Entrada inválida. Por favor, digite um número.")
#        else: # Palpites subsequentes
#            print(f"Palpites anteriores: ")
#            for i in range(4):
#                if previous_guesses[i] is not None:
#                    print(f"Jogador {i}: {previous_guesses[i]}")
#                    sum_guesses += previous_guesses[i]
#            if n_previous_guesses == len([player for player in game.state['players_alive'] if player == True]) - 1: # Último palpite
#                while True:
#                    try:
#                        guess = int(input("Digite seu palpite: "))
#                        sum_guesses += guess
#                        if sum_guesses != game.get_round():
#                            self.set_guess(guess)
#                            return self.guess
#                        else:
#                            print(f"Seu palpite, em conjunto com os palpites anteriores, não pode ser igual ao número da rodada")
#                            sum_guesses -= guess
#                    except ValueError:
#                        print("Entrada inválida. Por favor, digite um número.")
#            else:
#                while True:
#                    try:
#                        guess = int(input("Digite seu palpite: "))
#                        self.set_guess(guess)
#                        return self.guess
#                    except ValueError:
#                        print("Entrada inválida. Por favor, digite um número.")

    # Escolhe uma carta para jogar e guarda no objeto
    def play_a_card(self, previous_cards):
        n_previous_cards = len([card for card in previous_cards if card is not None])
        if n_previous_cards == 0:
            print("VOCÊ É O PRIMEIRO A JOGAR, escolha uma carta: ")
            for i in range(len(self.cards)):
                print(f" {i+1}: {self.cards[i][0]} de {self.cards[i][1]}")
            while True:
                try:
                    card = int(input())
                    if 1 <= card <= len(self.cards):
                        break
                    else:
                        print("Número inválido. Por favor, escolha um número entre 1 e", len(self.cards))
                except ValueError:
                    print("Entrada inválida. Por favor, digite um número.")
            self.card_played = self.cards[card-1]
            self.cards.pop(card-1)
        else:
            print("Cartas jogadas anteriormente: ")
            for i in range(4):
                if previous_cards[i] is not None:
                    print(f"Jogador {i}: {previous_cards[i][0]} de {previous_cards[i][1]}")
            print("Escolha uma carta: ")
            for i in range(len(self.cards)):
                print(f" {i+1}: {self.cards[i][0]} de {self.cards[i][1]}")
            while True:
                try:
                    card = int(input())
                    if 1 <= card <= len(self.cards):
                        break
                    else:
                        print("Número inválido. Por favor, escolha um número entre 1 e", len(self.cards))
                except ValueError:
                    print("Entrada inválida. Por favor, digite um número.")
            self.card_played = self.cards[card-1]
            self.cards.pop(card-1)
        
#    # Perde vidas
#    def lose_lifes(self, points):
#        number_of_lost_lifes = abs(points - self.guess)    
#        self.lifes -= number_of_lost_lifes
#        print(f"Número de vidas perdidas: {number_of_lost_lifes}. Vidas restantes: {self.lifes}")

    # Mostra que todos perderam
    def all_losers(self):
        print("Todos os jogadores estouraram!")
    
    # Mostra o vencedor do jogo
    def game_winner(self, winner):
            if winner == self.index:
                print("Você venceu!")
            else:
                print(f"O jogador {winner} venceu!")

    def player_action(self, game):
        while True:
            print(f"Sua mão: {self.cards} (valor: {game.calculate_hand_value(self.cards)})")
            action = input("Digite 'hit' para pedir uma carta ou 'stand' para parar: ").strip().lower()
            if action == 'hit':
                new_card = game.state['deck'].pop()  # Pega uma carta do baralho
                self.cards.append(new_card)
                print(f"Você recebeu: {new_card}")
                if game.calculate_hand_value(self.cards) > 21:
                    print("Você estourou! (Bust)")
                    game.kill_player(self.index)
                    break
            elif action == 'stand':
                game.state['points'][self.index] = game.calculate_hand_value(self.cards)
                break
            else:
                print("Ação inválida. Por favor, digite 'hit' ou 'stand'.")
    
    def dealer_action(self, game):
        print(f"Dealer está jogando...")
        while True:
            hand_value = game.calculate_hand_value(self.cards)
            print(f"Dealer: {self.cards} (valor: {hand_value})")
            if hand_value < 17:  # Regra do dealer: continuar até atingir pelo menos 17
                new_card = game.state['deck'].pop()  # Pega uma carta do baralho
                self.cards.append(new_card)
                print(f"Dealer recebeu: {new_card}")
            else:
                print(f"Dealer parou com: {self.cards} (valor: {hand_value})")
                return 'stand' if hand_value <= 21 else 'bust'

    """# Rotina do dealer e do jogador que torna
    def dealer_routine(self, player, game, socket_sender, socket_receiver, NEXT_NODE_ADDRESS):
        while True:
            # Inicializar o round (apenas o dealer)
            if game.state['round'] == 1:
                guesses = 0
                game.set_current_dealer(player.index) # Define o dealer
                game.initialize_deck() # Inicializa o baralho
                game.shuffle_deck() # Embaralha o baralho
                cards_to_send = game.draw_cards(20) # Sorteia as cartas
                send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS) # Envia o estado do jogo
                print(f"-----------------RODADA {game.state['round']}-----------------")
                #self.set_vira(game.state['vira']) # Recebe o vira
                cards = send_broadcast(socket_sender, socket_receiver, "CARDS", cards_to_send, player.index, NEXT_NODE_ADDRESS) # Envia as cartas para os jogadores
                self.set_cards(cards[player.index]) # Recebe as cartas do dealer
                #guesses = send_broadcast(socket_sender, socket_receiver, "TAKE-GUESSES", game.get_guesses(), player.index, NEXT_NODE_ADDRESS) # Pede os palpites
                #self.make_a_guess(game, guesses) # Dealer faz o palpite
                #guesses[player.index] = self.guess # Palpite do dealer
                #game.load_guesses(guesses) # Carrega os palpites no jogo
                #send_broadcast(socket_sender, socket_receiver, "SHOW-GUESSES", guesses, player.index, NEXT_NODE_ADDRESS) # Envia os palpites
                #self.show_guesses(guesses) # Mostra os palpites
            # -------------------------------------------------------------------------------------------------
            # Rotina compartilhada entre o dealer e o jogador que torna:

            # Manda a mensagem para coletar as cartas jogadas 
            # e recebe as cartas jogadas
            self.play_a_card([]) # Dealer joga uma carta
            game.set_card_played(game.state['cards_played'], self.card_played, self.index) # Adiciona a carta jogada ao jogo
            cards_played = send_broadcast(socket_sender, socket_receiver, "PLAY-CARD", game.get_cards_played(), player.index, NEXT_NODE_ADDRESS) # Envia a mensagem para jogarem as cartas
            game.set_cards_played(cards_played) # Recebe as cartas jogadas
            send_broadcast(socket_sender, socket_receiver, "SHOW-CARDS", game.get_cards_played(), player.index, NEXT_NODE_ADDRESS) # Envia as cartas jogadas
            self.show_cards(game.get_cards_played()) # Mostra as cartas jogadas
            subround_winner = game.end_of_sub_round(game.get_cards_played()) # Contabiliza quem fez a rodada
            self.sub_round_winner(subround_winner) # Mostra o vencedor da sub-rodada
            send_broadcast(socket_sender, socket_receiver, "SUBROUND-WINNER", subround_winner, player.index, NEXT_NODE_ADDRESS) # Envia o vencedor da sub-rodada
            game.increment_sub_rounds() # Incrementa a rodada
            # Validação de fim de rodada
            if game.state['n_sub_rounds'] == game.state['round']: # Fim da rodada
                round_evaluation = game.end_of_round() # Avalia a situação pós-rodada
                dealer_points = send_broadcast(socket_sender, socket_receiver, "END-OF-ROUND", game.state['points'], player.index, NEXT_NODE_ADDRESS) # Passa os resultados da rodada
                self.lose_lifes(dealer_points[player.index]) # Perde vidas
                game.reset_points() # Reseta os pontos
                if round_evaluation == -1: # Ninguém ganhou
                    game.increment_round() # Incrementa a rodada
                    next_dealer = game.next_dealer() # Pega o próximo dealer
                    game.reset_sub_rounds() # Reseta o número de sub-rodadas
                    if next_dealer != player.index:
                        send_unicast(socket_sender, socket_receiver, "TOKEN", (next_dealer, game.state), player.index, NEXT_NODE_ADDRESS) # Passa o token para o próximo dealer
                        return 0 # Retorna 0 para indicar que a sub-rotina desse nodo terminou
                    continue

                elif round_evaluation == -2: # Empate
                    self.all_losers()
                    send_broadcast(socket_sender, socket_receiver, "TIE", round_evaluation, player.index, NEXT_NODE_ADDRESS)
                    return 1
                else: # Tem um vencedor
                    self.game_winner(round_evaluation) # Anuncia o vencedor
                    send_broadcast(socket_sender, socket_receiver, "WINNER", round_evaluation, player.index, NEXT_NODE_ADDRESS)
                    return 1
                # return 0 # Retorna 0 para indicar que a sub-rotina desse nodo terminou
            
            # Validação de quem torna:
            if subround_winner != player.index:
                send_unicast(socket_sender, socket_receiver, "TOKEN", (subround_winner, game.state), player.index, NEXT_NODE_ADDRESS) # Passa o token para quem vai "tornar" e se tornar o "dealer" da próxima rodada
                return 0 # Retorna 0 para indicar que a sub-rotina desse nodo terminou  
    """
    """
    def collect_bet(self, player_index, socket_sender, socket_receiver, NEXT_NODE_ADDRESS):
        Método para coletar a aposta de um jogador.
        Este método pode envolver a comunicação via socket para receber a aposta do jogador.
        
        # Envia uma mensagem para o jogador pedindo a aposta
        bet_message = f"Jogador {player_index}, por favor, faça sua aposta:"
        
        # Aqui, você deve passar NEXT_NODE_ADDRESS corretamente para o sendto
        socket_sender.sendto(bet_message.encode(), NEXT_NODE_ADDRESS)  # Certifique-se de enviar o endereço correto
        
        # Recebe a aposta do jogador (simulação simples)
        bet, _ = socket_receiver.recvfrom(1024)  # Espera uma resposta com a aposta
        return int(bet.decode())  # Retorna a aposta como um inteiro
    """          
    def dealer_routine(self, player, game, socket_sender, socket_receiver, NEXT_NODE_ADDRESS):
        while True:
            # Inicializar a rodada (apenas o dealer)
            if game.state['round'] == 1:
                print(f"-----------------RODADA {game.state['round']}-----------------")
                game.set_current_dealer(player.index)  # Define o dealer
                game.initialize_deck()  # Inicializa o baralho
                game.shuffle_deck()  # Embaralha o baralho
                cards_to_send = game.draw_cards() # todas as cartas
                jogadas = 0
                
                # Coletar apostas dos jogadores
                #bets = {}
                #for i in range(game.n_players):
                #    if i != player.index:  # Apenas jogadores (exclui o dealer)
                #        bet = player.collect_bet(i, socket_sender, socket_receiver, NEXT_NODE_ADDRESS)
                #        bets[i] = bet
                #game.state['bets'] = bets

                print(f"player.index: {player.index}")
                send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS) # Envia o estado do jogo
                
                # Distribuir cartas iniciais (2 para cada jogador e dealer)
                cards = send_broadcast(socket_sender, socket_receiver, "CARDS", cards_to_send, player.index, NEXT_NODE_ADDRESS) # Envia as cartas para os jogadores
                self.set_cards(cards[player.index]) # Recebe as cartas do dealer
                cards = send_broadcast(socket_sender, socket_receiver, "CARDS", cards_to_send, player.index, NEXT_NODE_ADDRESS) # Envia as cartas para os jogadores
                self.set_cards(cards[player.index]) # Recebe as cartas do dealer
                # Envia o estado inicial para todos
                #send_broadcast(socket_sender, socket_receiver, "INITIAL-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS)
            
            # Ações dos jogadores (excluindo o dealer)
            #for i in range(game.n_players):
            #    if i != player.index and game.state['players_alive'][i]:  # Apenas jogadores ativos
            jogadas = send_broadcast(socket_sender, socket_receiver, "PLAYER-ACTION" , game.get_state(), player.index, NEXT_NODE_ADDRESS)
            
            # Ação do dealer
            self.dealer_action(game)

            # Avaliação da rodada
            winners = send_broadcast(socket_sender, socket_receiver, "END-OF-ROUND" , game.get_state(), player.index, NEXT_NODE_ADDRESS)

            ##self.announce_results(winners)  # Anuncia os vencedores

            # Reseta o estado do jogo para a próxima rodada
            reset = send_broadcast(socket_sender, socket_receiver, "END-OF-ROUND" , game.get_state(), player.index, NEXT_NODE_ADDRESS)
            next_dealer = game.state['dealer']
            if next_dealer != player.index:
                send_unicast(socket_sender, socket_receiver, "TOKEN", (next_dealer, game.state), player.index, NEXT_NODE_ADDRESS)
                return 0  # Passa o controle para o próximo dealer

    def send_deal_cards(socket_sender, socket_receiver, game, sender_index, NEXT_NODE_ADDRESS):
        message = game.deal_initial_cards()  # Função que retorna cartas distribuídas
        send_broadcast(socket_sender, socket_receiver, "DEAL-CARDS", message, sender_index, NEXT_NODE_ADDRESS)
    
    def send_player_action(socket_sender, action, player_index, NEXT_NODE_ADDRESS):
        message = {"player": player_index, "action": action}
        send_unicast(socket_sender, None, "PLAYER-ACTION", message, player_index, NEXT_NODE_ADDRESS)
    
    def send_game_result(socket_sender, socket_receiver, game, sender_index, NEXT_NODE_ADDRESS):
        results = game.evaluate_round()  # Calcula os resultados da rodada
        send_broadcast(socket_sender, socket_receiver, "GAME-RESULT", results, sender_index, NEXT_NODE_ADDRESS)
