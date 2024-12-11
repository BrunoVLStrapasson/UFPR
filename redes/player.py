# Jogo black jack desenvolvido numa rede em anel, disciplina redes1
# Bruno Vila Lobus Strapasson - GRR20215522
# Vinicius de Paula - GRR20190360


from network import send_broadcast, send_unicast

class Player:
    def __init__(self, index):
        self.lifes = 1
        self.cards = []
        self.pnts =  None
        self.guess = None
        self.cash = 1000
        self.index = index

    # Métodos set
    def set_lifes(self, lifes):
        self.lifes = 0

    def set_pnts(self, pnts):
        self.pnts = pnts

    def set_cards(self, cards):
        self.cards = cards 

    def set_cash(self, cash):
        self.cash = cash

    def set_guess(self, guess):
        self.guess = guess

    def set_index(self, index):
        self.index = index

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
    
    def sub_round_winner(self, winner): 
        print(f"O jogador {self.index} {winner[self.index]}!")

    # Mostra todos os pONTOS
    def show_points(self, pontos):
        #print("\n")
        print(f"Jogador {self.index} : {self.pnts} pontos")
  
    def show_guesses(self, guesses):
        print("Palpites: ")
        for i in range(4):
            if guesses[i] is not None:
               print(f"Jogador {i}: {guesses[i]}")


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

    def main_round(self, player, game, socket_sender, socket_receiver, NEXT_NODE_ADDRESS):
        while True:
            # Inicializa o round
            if game.state['round']:
                guesses = 0
                game.set_current_dealer(player.index)  # Define o dealer
                game.initialize_deck()  # Inicializa o baralho
                game.shuffle_deck()  # Embaralha o baralho
                cards_to_send = game.draw_cards()  # Todas as cartas

                send_broadcast(socket_sender, socket_receiver, "GAME-STATE", game.get_state(), player.index, NEXT_NODE_ADDRESS)  # Envia o estado do jogo
                print(f"\nROUND : {game.state['round']}\n")
                
                guesses = send_broadcast(socket_sender, socket_receiver, "TAKE-GUESSES", game.get_guesses(), player.index, NEXT_NODE_ADDRESS) # Pede os palpites
                self.make_a_guess(game, guesses) # Dealer faz o palpite

            # Distribui cartas para os jogadores
            cards = send_broadcast(socket_sender, socket_receiver, "CARDS", cards_to_send, player.index, NEXT_NODE_ADDRESS)  # Envia as cartas
            self.set_cards(cards[player.index])  # Recebe as cartas do dealer

            # Ações dos jogadores (excluindo o dealer)
            jogadas = 0
            jogadas = send_broadcast(socket_sender, socket_receiver, "PLAYER-ACTION", game.get_points_played(), player.index, NEXT_NODE_ADDRESS)
            #dealer joga
            self.dealer_action(game)
            jogadas[0] = self.pnts
            game.set_points_played(game.state['points_played'], jogadas, player.index)

            #mostra todas os pontos quee cada jogador conquistou durante a rodada
            send_broadcast(socket_sender, socket_receiver, "SHOW-CARDS", game.get_points_played(), player.index, NEXT_NODE_ADDRESS) 
            self.show_points(game.get_points_played())

            #vetor subround_winner retorna a situacao de cada jogador , ganhou ,perdeu ou empatou
            subround_winner = game.end_of_sub_round() # Contabiliza quem fez a rodada
            send_broadcast(socket_sender, socket_receiver, "SUBROUND-WINNER", subround_winner, player.index, NEXT_NODE_ADDRESS) 
            
            #funcionando retorno das apostas para cada jogador
            send_broadcast(socket_sender, socket_receiver, "CONTABILIZE", subround_winner, player.index, NEXT_NODE_ADDRESS) 
            self.retorna_guess(subround_winner)

            #avalia se jogador tem cash se nao tiver eh expulso
            send_broadcast(socket_sender, socket_receiver, "CASH-AVAL", game.get_guesses(), player.index, NEXT_NODE_ADDRESS)

            next_dealer = game.next_dealer()
            print(f"proximo dealer sera {next_dealer}")            
            game.increment_round() # Incrementa a rodada
            
            cont = 0
            if next_dealer != self.index:
                for i in range(game.n_players):
                    if game.state['players_lifes'][i] == 0:
                        cont = cont + 1
                #se tem 3 jogadores mortos o jogo acaba
                if cont == 3:
                    send_broadcast(socket_sender, socket_receiver, "END-CONNECTION", ("END-CONNECTION"), player.index, NEXT_NODE_ADDRESS)
                    print("Conexões encerradas. Dealer saindo do jogo.")
                    return -1
                #reiniciar o round com um novo dealer
                #passagem do bastao para o proximo dealer
                send_unicast(socket_sender, socket_receiver, "TOKEN", (next_dealer, game.state), player.index, NEXT_NODE_ADDRESS)
                return 0
