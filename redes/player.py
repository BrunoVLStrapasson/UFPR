from network import send_broadcast, send_unicast

class Player:
    def __init__(self, index):
        self.lifes = 1
        self.cards = []
        #self.vira = None
        self.pnts =  0
        self.guess = None
        self.cash = 1000
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

    def set_pnts(self, pnts):
        self.pnts = pnts

    def set_cards(self, cards):
        self.cards = cards  # Define as cartas do jogador

    def set_cash(self, cash):
        self.cash = cash

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

    def retorna_guess(self, winner):
        if winner[self.index] == 'empatou':
            self.cash += self.guess
            print(f"\njogador {self.index} apos a rodada esta com {self.cash} fichas\n")
        if winner[self.index] == 'ganhou':
            self.cash += 2*self.guess
            print(f"\njogador {self.index} apos a rodada esta com {self.cash} fichas\n")
        if winner[self.index] == 'dealer':
            self.cash += self.guess
            print(f"\njogador {self.index} apos a rodada esta com {self.cash} fichas\n")
        if winner[self.index] == 'perdeu':
            print(f"\njogador {self.index} apos a rodada esta com {self.cash} fichas\n")    


    # Métodos get
    def get_cash(self):
        return self.cash

    def get_lifes(self):
        return self.lifes

    def get_cards(self):
        return self.cards

    def get_pnts(self):
        return self.pnts

    def get_guess(self):
        return self.guess

    def get_index(self):
        return self.index

    def get_card_played(self):
        return self.card_played
    
    def sub_round_winner(self, winner): 
        print(f"O jogador {self.index} {winner[self.index]}!")

    # Mostra todos os pONTOS
    def show_points(self, pontos):
        #print("\n")
        print(f"Jogador {self.index} : {self.pnts} pontos")
  
    # Mostra todos os palpites feitos
    def show_guesses(self, guesses):
        print("Palpites: ")
        for i in range(4):
            if guesses[i] is not None:
               print(f"Jogador {i}: {guesses[i]}")

    # Faz um palpite e guarda no objeto 
    def make_a_guess(self, game, previous_guesses):
        n_previous_guesses = 0

        # Primeiro palpite da rodada
        if n_previous_guesses == 0:
            while True:
                try:
                    print(f"Você tem {self.cash} fichas.")
                    guess = int(input("Digite sua aposta: "))
                    
                    # Verifica se a aposta é válida
                    if 0 < guess <= self.cash:
                        self.cash -= guess  # Deduz a aposta do saldo
                        self.guess = guess  # Registra a aposta
                        print(f"Aposta de {guess} fichas realizada. Você agora tem {self.cash} fichas restantes.")
                        self.set_guess(guess)
                        return self.guess
                    else:
                        print(f"Por favor, digite um número entre 1 e {self.cash}.")
                except ValueError:
                    print("Entrada inválida. Por favor, digite um número.")

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
            
    def reset_cards(self):
        self.cards = []

    def all_losers(self):
        print("Todos os jogadores estouraram!")
    
    # Mostra o vencedor do jogo
    def game_winner(self, winner):
            if winner == self.index:
                print("Você venceu!")
            else:
                print(f"O jogador {winner} venceu!")

    def player_action(self, game):
        aux = 0
        while True:
            print(f"Sua mão: {self.cards} (valor: {game.calculate_hand_value(self.cards)})")
            action = input("Digite 'hit' para pedir uma carta ou 'stand' para parar: ").strip().lower()
            if action == 'hit':
                new_card = game.state['deck'].pop()  # Pega uma carta do baralho
                self.cards.append(new_card)
                print(f"Você recebeu: {new_card}")
                if game.calculate_hand_value(self.cards) > 21:
                    aux = game.calculate_hand_value(self.cards)
                    self.pnts = aux
                    self.set_pnts(aux)
                    print("Você estourou! (Bust)")
                    return self.pnts
            elif action == 'stand':
                # Atualiza o valor dos pontos do jogador no vetor global de pontos
                aux = game.calculate_hand_value(self.cards)
                self.pnts = aux
                self.set_pnts(aux)
                return self.pnts
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
                aux = game.calculate_hand_value(self.cards)
                self.set_pnts(aux)
                return 'stand' if hand_value <= 21 else 'bust'

    """   # Rotina do dealer e do jogador que torna
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

    def dealer_routine(self, player, game, socket_sender, socket_receiver, NEXT_NODE_ADDRESS):
        while True:
            # Inicializa a rodada (apenas o dealer)
            if game.state['round']:
                guesses = 0
                game.set_current_dealer(player.index)  # Define o dealer
                game.initialize_deck()  # Inicializa o baralho
                game.shuffle_deck()  # Embaralha o baralho
                cards_to_send = game.draw_cards()  # Todas as cartas

                send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS)  # Envia o estado do jogo
                #print(f"player.index: {player.index}")
                print(f"\n-----------------RODADA {game.state['round']}-----------------\n")
                

                guesses = send_broadcast(socket_sender, socket_receiver, "TAKE-GUESSES", game.get_guesses(), player.index, NEXT_NODE_ADDRESS) # Pede os palpites
                self.make_a_guess(game, guesses) # Dealer faz o palpite
                #guesses[player.index] = self.guess # Palpite do dealer
                #game.load_guesses(guesses) # Carrega os palpites no jogo

                #send_broadcast(socket_sender, socket_receiver, "SHOW-GUESSES", guesses, player.index, NEXT_NODE_ADDRESS) # Envia os palpites
                    #self.show_guesses(guesses) # Mostra os palpites

                # Distribui cartas para os jogadores
            cards = send_broadcast(socket_sender, socket_receiver, "CARDS", cards_to_send, player.index, NEXT_NODE_ADDRESS)  # Envia as cartas
            self.set_cards(cards[player.index])  # Recebe as cartas do dealer

            # Ações dos jogadores (excluindo o dealer)
            jogadas = 0
            jogadas = send_broadcast(socket_sender, socket_receiver, "PLAYER-ACTION", game.get_points_played(), player.index, NEXT_NODE_ADDRESS)
            #game.set_points_played(game.state['points_played'],jogadas,self.index) # Recebe as cartas jogadas
            self.dealer_action(game)
            jogadas[0] = self.pnts
            game.set_points_played(game.state['points_played'], jogadas, player.index)
            #print(jogadas)

            #mostra todas os pontos quee cada jogador conquistou durante a rodada
            send_broadcast(socket_sender, socket_receiver, "SHOW-CARDS", game.get_points_played(), player.index, NEXT_NODE_ADDRESS) # Envia as cartas jogadas
            self.show_points(game.get_points_played())

            subround_winner = game.end_of_sub_round() # Contabiliza quem fez a rodada
            #self.sub_round_winner(subround_winner) # Mostra o vencedor da sub-rodada
            send_broadcast(socket_sender, socket_receiver, "SUBROUND-WINNER", subround_winner, player.index, NEXT_NODE_ADDRESS) # Envia o vencedor da sub-rodada
            #vetor subround_winner retorna a situacao de cada jogador , ganhou ,perdeu ou empatou
            #print(subround_winner)
            
            #funcionando retorno das apostas para cada jogador
            send_broadcast(socket_sender, socket_receiver, "CONTABILIZA", subround_winner, player.index, NEXT_NODE_ADDRESS) # Envia as cartas jogadas
            self.retorna_guess(subround_winner)
            
            #print(f"aposta de cada jogador {self.guess}")

#            if cash de cada jogador = 0 entao o jogo acaba, ou quando restar apenas 1 com dinheiro.

            #reset = send_broadcast(socket_sender, socket_receiver, "RESET", None, player.index, NEXT_NODE_ADDRESS)

            next_dealer = game.next_dealer()
            print(f"proximo dealer sera {next_dealer}")

            #send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS)  # Envia o estado do jogo
            
            game.increment_round() # Incrementa a rodada
            #passagem do bastao para o proximo dealer
            
            if next_dealer != self.index:
                #print("chegou no unicast")
                send_unicast(socket_sender, socket_receiver, "TOKEN", (next_dealer, game.state), player.index, NEXT_NODE_ADDRESS)
                return 0  # Passa o controle para o próximo dealer
            #continue
            #parei aqui por enquanto
            #retornar as apostas para cada jogador
            #reiniciar o round com um novo dealer pode ser o proximo

            # Validação de quem torna:
            if subround_winner != self.index:
                print("Passou aqui")
                #send_unicast(socket_sender, socket_receiver, "TOKEN", (2, game.state), player.index, NEXT_NODE_ADDRESS) # Passa o token para quem vai "tornar" e se tornar o "dealer" da próxima rodada
                #return 0 # Retorna 0 para indicar que a sub-rotina desse nodo terminou  

"""
            send_broadcast(socket_sender, socket_receiver, "SHOW-POINTS", jogadas, player.index, NEXT_NODE_ADDRESS) # Envia os palpites
            #self.show_guesses(guesses) # Mostra os palpites

            send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS)  # Envia o estado do jogo
            

            #send_broadcast(socket_sender, socket_receiver, "PLAYER-POINTS", game.get_state(), player.index, NEXT_NODE_ADDRESS)

            # Avaliação da rodada
            game.end_of_round()

            # Anunciar o fim da rodada e passar os resultados para os jogadores
            winners = send_broadcast(socket_sender, socket_receiver, "END-OF-ROUND", game.state, player.index, NEXT_NODE_ADDRESS)

            # Resetar as cartas e reiniciar a rodada
            self.reset_cards(

"""