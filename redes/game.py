# Jogo black jack desenvolvido numa rede em anel, disciplina redes1
# Bruno Vila Lobus Strapasson - GRR20215522
# Vinicius de Paula - GRR20190360

import random 

class Game:
    def __init__(self):
        self.n_players = 4  # Número de jogadores
        self.state = {
            'round': 1,  # Rodada inicial
            'dealer': 0,  # Índice do dealer
            'players_alive': [True,True,True,True],  # Status de jogadores
            'players_lifes' : [1, 1, 1, 1],
            'deck': [],  # Mãos dos jogadores
            'guesses': [0,0,0,0],  # Apostas dos jogadores
            'points_played' : [0,0,0,0],
        }

    def __str__(self):
        return f"Round: {self.state['round']}, Deck: {self.state['deck']}, Player Lifes: {self.state['players_lifes']}, Players Alive: {self.state['players_alive']}, Guesses: {self.state['guesses']}, Points_played: {self.state['points']}, Dealer: {self.state['dealer']}"

    def set_points_played(self, points_played, point, index):

        # Certifica-se de que `points_played` seja uma lista simples
        if not isinstance(self.state['points_played'], list) or len(self.state['points_played']) != self.n_players:
            self.state['points_played'] = [0] * self.n_players

        # Atualiza o índice específico com o valor fornecido
        self.state['points_played'] = point
    
    def set_card_played(self, cards_played, card, index):
        cards_played[index] = card
        self.state['cards_played'] = cards_played

    def set_cards_played(self, cards_played):
        self.state['cards_played'] = cards_played

    # Atribui o dealer atual
    def set_current_dealer(self, dealer):
        self.state['current_dealer'] = dealer

    def set_state(self, state):
        self.state = state

    def set_round(self, round):
        self.state['round'] = round

    def set_players_lifes(self, index):
        self.state['players_lifes'][index] = 0
    
    def get_round(self):
        return self.state['round']
    
    def get_guesses(self):
        return self.state['guesses']

    def get_points_played(self):  
        return self.state['points_played']
    
    def get_players_lifes(self):  
        return self.state['players_lifes']
  
    def get_state(self):
        return self.state   

    def get_cards_played(self):
        return self.state['cards_played']   

    # Carrega os guesses
    def load_guesses(self, guesses):
        self.state['guesses'] = guesses 

    # Soma o n de rounds
    def increment_round(self):
        self.state['round'] += 1

    # Reseta os palpites
    def reset_guesses(self):
        self.state['guesses'] = [None, None, None, None]

    def assign_dealer(self):
        # Defina um jogador como o dealer
        self.state['dealer'] = 0  # Por exemplo, o primeiro jogador é o dealer    
     
    def reset_card_played(self):
        self.state['cards_played'] = [None, None, None, None]
     
    def calculate_hand_value(self, hand):
            value = 0
            aces = 0
            for card in hand:
                if card == 1:  # Ás
                    aces += 1
                    value += 11  # Considerar Ás como 11 por padrão
                elif card in [11, 12, 13]:  # J, Q, K
                    value += 10
                else:
                    value += card  # Cartas de valor numérico
            # Ajuste para Ás, caso a soma seja maior que 21
            while value > 21 and aces:
                value -= 10
                aces -= 1
            return value

    # Inicilializa o baralho
    def initialize_deck(self):
            # Cria um baralho de 10 valores (1-10)
            self.state['deck'] = [value for value in range(1, 13)] * 4  # 4 naipes (ignorados)

    def draw_cards(self):
        n_players_alive = self.state['players_alive'].count(True)
        g_cards = [[] for _ in range(self.n_players)]  # Inicializa g_cards como lista de listas
        n_max_cards = int(40 / n_players_alive) - 1 # Número máximo de cards por player
        n_cards_to_give = 0 # Número de cartas a serem dadas
        if self.state['round'] > n_max_cards:
            n_cards_to_give = n_max_cards
        else:
            n_cards_to_give = 2
        for i in range(self.n_players):
            if self.state['players_alive'][i]:
                for _ in range(n_cards_to_give):
                    g_cards[i].append(self.state['deck'].pop())
            else: # Se o jogador não estiver vivo, ele não recebe cartas
                g_cards[i] = None
        self.state['vira'] = self.state['deck'].pop() # Vira é a última carta removida do baralho
        return g_cards 
        
    def load_points(self, points):
        self.state['points'] = points

    # Embaralha o baralho
    def shuffle_deck(self):
        random.shuffle(self.state['deck'])

    # Mata um jogador
    def kill_player(self, index):
        self.set_players_lifes(index)
        print(self.state['players_lifes'])
    
    def check_winner(self, players):
        # Retorna o vencedor com maior pontuação ≤ 21
        scores = [(i, self.calculate_hand_value(player.cards)) for i, player in enumerate(players)]
        scores = [(i, score) for i, score in scores if score <= 21]
        if scores:
            return max(scores, key=lambda x: x[1])[0]  # Retorna índice do vencedor
        return None  # Todos perderam                   
    
    def reset_points(self):
        self.state['points'] = [0, 0, 0, 0]

    def update_player_points(self):
            # Atualiza os self.['points_played'] de todos os jogadores
            for i in range(self.n_players):
                if self.state['players_alive'][i]:  # Se o jogador estiver vivo
                    # Aqui você calcula o valor das cartas do jogador (supondo que 'cards' sejam as cartas)
                    # Como você não possui um vetor de jogadores, vamos supor que as cartas estão em state['deck'][i]
                    self.state['points'][i] = self.calculate_hand_value(self.state['deck'][i])  # Atualiza os self.['points_played']
    
    # Contabiliza as cartas jogadas
    def end_of_sub_round(self):
        print("\n-------- Fim da Rodada --------\n")
        print(" Pontos totais de cada jogador:")
        print(f"      {self.state['points_played']}")
        
        dealer_index = self.state['dealer']
        dealer_points = self.state['points_played'][dealer_index]  # Pontos do dealer
        #print(f"\nDealer: {dealer_points} pontos. ")

        winners = ['dealer' if i == dealer_index else None for i in range(self.n_players)]

        if dealer_points > 21:
            winners = ['dealer','empatou','empatou','empatou']
            return winners

        for i in range(self.n_players):
            if i == dealer_index or not self.state['players_alive'][i]:
                continue

            player_points = self.state['points_played'][i]
            #print('points_played'[i])
            if player_points > dealer_points and player_points <= 21:
                print(f"Jogador {i} venceu o Dealer!")
                winners[i] = 'ganhou'
            elif player_points == dealer_points:
                print(f"Jogador {i} empatou com o Dealer.")
                winners[i] = 'empatou'
            else:
                print(f"Jogador {i} perdeu para o Dealer.")
                winners[i] = 'perdeu'

        return winners

    def evaluate_round(self):
        # Vetor para armazenar os valores das mãos dos jogadores
        hands_values = [None] * self.n_players

        # Calcular os valores das mãos
        for i in range(self.n_players):
            if not self.state['players_alive'][i]:  # Jogador eliminado ou estourado
                hands_values[i] = -1  # Indica jogador estourado
            else:
                hands_values[i] = self.calculate_hand_value(self.state['cards_playde'])

        # Determinar o vencedor:
        # O dealer é comparado com os jogadores vivos
        dealer_index = self.state['dealer']
        dealer_value = hands_values[dealer_index]

        print(f"Dealer:  (valor: {dealer_value})")

        # Lista para armazenar os vencedores
        winners = []

        for i in range(self.n_players):
            if i == dealer_index:  # Ignorar o dealer na comparação
                continue

            player_value = hands_values[i]

            print(f"Jogador {i}:  (valor: {player_value})")

            if not self.state['players_alive'][i]:  # Jogador estourou
                print(f"Jogador {i} está fora da rodada. (Bust)")
            elif dealer_value > 21 or (player_value <= 21 and player_value > dealer_value):  
                # Dealer estourou ou jogador tem maior valor válido
                print(f"Jogador {i} venceu o dealer!")
                winners.append(i)
            elif player_value == dealer_value:
                # Empate
                print(f"Jogador {i} empatou com o dealer.")
            else:
                # Dealer venceu
                print(f"Jogador {i} perdeu para o dealer.")

        return winners

    # Pega o próximo jogador VIVO para ser o dealer
    def next_dealer(self):
        # Obtem o dealer atual
        current_dealer = self.state.get('dealer', -1)  # Dealer atual (-1 se nenhum dealer inicial foi definido)
        
        # Cria uma lista de jogadores candidatos ao sorteio (todos menos o dealer atual)
        candidates = [i for i in range(self.n_players) if i != current_dealer]
        
        if not candidates:
            raise ValueError("Não há jogadores disponíveis para ser o novo dealer.")
        
        # Sorteia o novo dealer
        new_dealer = random.choice(candidates)
        
        # Atualiza o estado do jogo
        self.state['dealer'] = new_dealer
        
        return new_dealer

