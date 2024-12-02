# ALTERAR PARA Q A ORDEM DE ANÁLISE COMECE SEMPRE PELO CARTEADOR
import random 

# class Game:
#     def __init__(self):
#         self.n_players = 4
#         self.state = {
#             'deck' : [],
#             'round' : 1,
#             'n_sub_rounds' : 0,
#             'n_sub_rounds' : 0,
#             'current_dealer' : None,
#             'players_lifes' : [3, 3, 3, 3],
#             'players_alive': [True, True, True, True],
#             'guesses' : [None, None, None, None],
#             'cards_played' : [None, None, None, None],
#             'points' : [0, 0, 0, 0],
#             'vira' : None,
#         }

class Game:
    def __init__(self):
        self.n_players = 4  # Número de jogadores, por exemplo
        self.state = {
            'round': 1,  # Rodada inicial
            'dealer': 0,  # Índice do dealer
            'players_alive': [True,True,True,True],  # Status de jogadores
            'players_lifes' : [1, 1, 1, 1],
            'deck': [],  # Mãos dos jogadores
            'points': [0,0,0,0],  # Apostas dos jogadores
            # Adicione outras chaves relevantes aqui
        }

    def assign_dealer(self):
        # Defina um jogador como o dealer
        self.state['dealer'] = 0  # Por exemplo, o primeiro jogador é o dealer
        # Você pode mudar isso conforme as regras do jogo
    
    def __str__(self):
        return f"Deck: {self.state['deck']}, Round: {self.state['round']}, Current Dealer: {self.state['current_dealer']}, Player Lifes: {self.state['players_lifes']}, Players Alive: {self.state['players_alive']}, Guesses: {self.state['guesses']}, Points: {self.state['points']}, Vira: {self.state['vira']}"

    # Carrega os guesses
    def load_guesses(self, guesses):
        self.state['guesses'] = guesses 

    def set_round(self, round):
        self.state['round'] = round
    
    def get_round(self):
        return self.state['round']
    
    def get_guesses(self):  
        return self.state['guesses']

    # Soma o n de subrodadas
    def increment_sub_rounds(self):
        self.state['n_sub_rounds'] += 1

    # Soma o n de rounds
    def increment_round(self):
        self.state['round'] += 1

    # Reseta o número de subrodadas
    def reset_sub_rounds(self):
        self.state['n_sub_rounds'] = 0

    # Reseta os palpites
    def reset_guesses(self):
        self.state['guesses'] = [None, None, None, None]

    # Atribui o dealer atual
    def set_current_dealer(self, dealer):
        self.state['current_dealer'] = dealer

    def set_state(self, state):
        self.state = state
    
    def get_state(self):
        return self.state
    
    def set_card_played(self, cards_played, card, index):
        cards_played[index] = card
        self.state['cards_played'] = cards_played
    
    def set_cards_played(self, cards_played):
        self.state['cards_played'] = cards_played

    def get_cards_played(self):
        return self.state['cards_played']
     
    def reset_card_played(self):
        self.state['cards_played'] = [None, None, None, None]

    # Inicilializa o baralho
    def initialize_deck(self):
            # Cria um baralho de 10 valores (1-10)
            self.state['deck'] = [value for value in range(1, 13)] * 4  # 4 naipes (ignorados)
        
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

    def draw_cards(self):
        n_players_alive = self.state['players_alive'].count(True)
        g_cards = [[] for _ in range(self.n_players)]  # Inicializa g_cards como lista de listas
        n_max_cards = int(40 / n_players_alive) - 1 # Número máximo de cards por player
        n_cards_to_give = 0 # Número de cartas a serem dadas
        if self.state['round'] > n_max_cards:
            n_cards_to_give = n_max_cards
        else:
            n_cards_to_give = self.state['round'] 
        for i in range(self.n_players):
            if self.state['players_alive'][i]:
                for _ in range(n_cards_to_give):
                    g_cards[i].append(self.state['deck'].pop())
            else: # Se o jogador não estiver vivo, ele não recebe cartas
                g_cards[i] = None
        self.state['vira'] = self.state['deck'].pop() # Vira é a última carta removida do baralho
        return g_cards
    
        
    # Embaralha o baralho
    def shuffle_deck(self):
        random.shuffle(self.state['deck'])

    # Embuchadas:
    def embuchadas(self, cards_played):
        for i in range(self.n_players):
            for j in range(i+1, self.n_players):
                if cards_played[i][0] == cards_played[j][0]:
                    return i, j
    
    """    # Contabiliza as cartas jogadas
    def end_of_sub_round(self):
        # Vetor para armazenar os valores das mãos dos jogadores
        hands_values = [None] * self.n_players

        # Calcular os valores das mãos
        for i in range(self.n_players):
            if not self.state['players_alive'][i]:  # Jogador eliminado
                hands_values[i] = -1  # Indica jogador estourado
            else:
                hands_values[i] = self.calculate_hand_value(self.state['players'][i].cards)

        # Determinar o vencedor:
        # O dealer é comparado com os jogadores vivos
        dealer_index = self.state['dealer']
        dealer_value = hands_values[dealer_index]

        # Dealer estourou, todos os jogadores vivos ganham
        if dealer_value > 21:
            winners = [i for i in range(self.n_players) if hands_values[i] <= 21 and i != dealer_index]
            if winners:
                for winner in winners:
                    self.state['points'][winner] += 1
            return winners

        # Dealer não estourou, comparar com os jogadores
        winners = []
        for i in range(self.n_players):
            if i == dealer_index or not self.state['players_alive'][i]:  # Ignorar dealer ou jogadores eliminados
                continue
            player_value = hands_values[i]
            if player_value > 21:  # Jogador estourou
                continue
            elif player_value > dealer_value:  # Jogador vence
                winners.append(i)
                self.state['points'][i] += 1
            elif player_value == dealer_value:  # Empate com o dealer
                winners.append(i)  # Registrar como empate técnico (se necessário)

        return winners
    """

    def evaluate_round(self):
        # Vetor para armazenar os valores das mãos dos jogadores
        hands_values = [None] * self.n_players

        # Calcular os valores das mãos
        for i in range(self.n_players):
            if not self.state['players_alive'][i]:  # Jogador eliminado ou estourado
                hands_values[i] = -1  # Indica jogador estourado
            else:
                hands_values[i] = self.calculate_hand_value(self.state['players_alive'][i].cards)

        # Determinar o vencedor:
        # O dealer é comparado com os jogadores vivos
        dealer_index = self.state['dealer']
        dealer_value = hands_values[dealer_index]

        print(f"Dealer: {self.state['players'][dealer_index].cards} (valor: {dealer_value})")

        # Lista para armazenar os vencedores
        winners = []

        for i in range(self.n_players):
            if i == dealer_index:  # Ignorar o dealer na comparação
                continue

            player_value = hands_values[i]

            print(f"Jogador {i}: {self.state['players'][i].cards} (valor: {player_value})")

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

    # Mata um jogador
    def kill_player(self, index):
        self.state['players_alive'][index] = False
    
    def check_winner(self, players):
        # Retorna o vencedor com maior pontuação ≤ 21
        scores = [(i, self.calculate_hand_value(player.cards)) for i, player in enumerate(players)]
        scores = [(i, score) for i, score in scores if score <= 21]
        if scores:
            return max(scores, key=lambda x: x[1])[0]  # Retorna índice do vencedor
        return None  # Todos perderam                   
    

    def reset_round(self):
        print("Preparando para a próxima rodada...")
        self.state['hands'] = [[] for _ in range(self.n_players)]  # Limpa as mãos dos jogadores
        self.state['bets'] = [0] * self.n_players  # Reseta as apostas
        self.state['deck'] = self.initialize_deck()  # Recria o baralho
        self.shuffle_deck()  # Embaralha o baralho
        self.state['round'] += 1  # Incrementa o número da rodada
        self.state['dealer'] = self.next_dealer()  # Escolhe o próximo dealer
        print(f"Novo dealer: Jogador {self.state['dealer']}")

    
    def reset_points(self):
        self.state['points'] = [0, 0, 0, 0]

    def determine_winner(self):
        # Remove jogadores que não têm mais vidas
        for i in range(self.n_players):
            if self.state['players_lifes'][i] <= 0 and self.state['players_alive'][i]:
                self.kill_player(i)

        players_alive = self.state['players_alive'].count(True)

        if players_alive == 1:  # Apenas um jogador vivo, ele é o vencedor
            winner_index = self.state['players_alive'].index(True)
            print(f"Jogador {winner_index} é o vencedor!")
            return winner_index
        elif players_alive > 1:  # Mais de um jogador vivo, o jogo continua
            return -1
        else:  # Nenhum jogador vivo, verificar desempate por vidas
            max_lifes = max(self.state['players_lifes'])
            if self.state['players_lifes'].count(max_lifes) > 1:
                print("O jogo terminou em empate!")
                return -2  # Empate
            else:
                winner_index = self.state['players_lifes'].index(max_lifes)
                print(f"Jogador {winner_index} vence por ter mais vidas!")
                return winner_index
        
            
    def end_of_round(self):
        dealer_index = self.state['dealer']
        dealer_points = self.state['points'][dealer_index]
        print(f"Dealer (Jogador {dealer_index}): {dealer_points} pontos")

        # Variáveis para rastrear o vencedor
        winner_index = None
        highest_points = -1
        tie = False

        # Verifica os pontos de cada jogador
        for i in range(self.n_players):
            if not self.state['players_alive'][i]:
                print(f"Jogador {i} está fora do jogo.")
                continue

            player_points = self.state['points'][i]
            print(f"Jogador {i}: {player_points} pontos")

            if player_points > 21:  # Jogador estourou
                print(f"Jogador {i} estourou! Perde uma vida.")
                self.state['players_lifes'][i] -= 1
                self.kill_player(i)
            else:
                if player_points > highest_points:  # Novo vencedor
                    winner_index = i
                    highest_points = player_points
                    tie = False
                elif player_points == highest_points:  # Empate
                    tie = True

        # Agora comparamos o dealer com os jogadores
        if dealer_points > 21:  # O dealer estourou
            print("O dealer estourou! Jogadores vivos ganham!")
            tie = False
            winner_index = self.get_living_players()[0]  # O primeiro jogador vivo será o vencedor

        elif highest_points < dealer_points:  # Dealer venceu
            print(f"O dealer venceu com {dealer_points} pontos!")
            winner_index = dealer_index
            tie = False
        elif highest_points == dealer_points:  # Empate entre dealer e jogador(s)
            print("Houve um empate entre o dealer e um ou mais jogadores.")
            tie = True

        # Se o vencedor foi definido
        if winner_index is not None and not tie:
            print(f"Jogador {winner_index} venceu com {highest_points} pontos!")
        elif tie:
            print("O jogo terminou em empate entre os jogadores e o dealer.")

        return winner_index if winner_index is not None else -1