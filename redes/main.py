# Jogo black jack desenvolvido numa rede em anel, disciplina redes1
# Bruno Vila Lobus Strapasson - GRR20215522
# Vinicius de Paula - GRR20190360


import socket
from game import Game
from player import Player
from network import get_addresses, ring_messages
import sys
import termios

def clear_input_buffer():
    """Limpa o buffer de entrada do terminal."""
    termios.tcflush(sys.stdin, termios.TCIFLUSH)

def wait_for_user_confirmation():
    """Exibe uma introdução ao jogo e espera até que o usuário confirme que deseja iniciar a comunicação."""
    print("\nBem-vindo ao Jogo de BlackJack em Rede!\n")
    print("Neste jogo, você participará de uma partida de cartas onde a comunicação entre os jogadores é feita em uma rede em anel.")
    print("Cada jogador possui um turno para jogar, e as informações serão enviadas de um nó para o próximo até que o dealer processe as jogadas.")
    print("\nQuando solicitado, digite 'jogar' para confirmar que você está pronto para começar o jogo.")

    while True:
        user_input = input("Digite 'jogar' para iniciar o jogo: ").strip().lower()
        if user_input == "jogar":
            break
        else:
            print("Entrada inválida. Por favor, digite 'sim' para iniciar a comunicação.")

def main():
    """Função principal que coordena a inicialização e execução do jogo em rede."""
    # Obtém os endereços do nó atual e do próximo nó na rede
    current_node_address, next_node_address = get_addresses()

    # Inicializa os sockets para envio e recebimento de mensagens
    sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver_socket.bind(current_node_address[0])

    # Determina se o token está inicialmente disponível
    token_available = current_node_address[1] == 0

    # Criação do jogador e inicialização do jogo
    current_player = Player(current_node_address[1])
    game_instance = Game()
    game_state = 0  # Estado inicial do jogo

    # Aguarda a confirmação do usuário para iniciar
    wait_for_user_confirmation()

    # Loop principal do jogo
    while True:
        if token_available:
            # Executa a rotina do dealer quando o token está disponível
            game_state = current_player.main_round(
                current_player, game_instance, sender_socket, receiver_socket, next_node_address
            )
            token_available = False  # Token é usado

        elif game_state == 0:
            # Se o token não está disponível, espera mensagens da rede
            network_status = ring_messages(
                current_node_address, next_node_address, game_instance, receiver_socket, sender_socket, current_player
            )

            if network_status == 1:
                token_available = True
            elif network_status == 0:
                clear_input_buffer()
                break  # Finaliza a execução do programa

        elif game_state == -1:
            # Estado final do jogo
            clear_input_buffer()
            break

if __name__ == "__main__":
    main()
