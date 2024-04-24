import subprocess
import os

def run_make(command):
    print(f"Exécution de {command}...")
    result = subprocess.run([command], shell=True, capture_output=True, text=True)
    print(result.stdout)
    if result.stderr:
        print("Erreur:", result.stderr)

def check_relinking(target, make_command):
    initial_mtime = os.path.getmtime(target)
    run_make(make_command)  # Premier make (bonus ou normal)
    after_first_make_mtime = os.path.getmtime(target)
    run_make(make_command)  # Deuxième make (bonus ou normal)
    after_second_make_mtime = os.path.getmtime(target)

    if after_first_make_mtime != initial_mtime:
        print("Le premier make a modifié le fichier.")
    else:
        print("Le premier make n'a pas modifié le fichier.")
    
    if after_second_make_mtime != after_first_make_mtime:
        print("\033[91mRelinkage détecté: Le deuxième make a modifié le fichier.\033[0m")

    else:
        print("\033[93mAucun relinkage: Le deuxième make n'a pas modifié le fichier.\033[0m")

if __name__ == "__main__":
    target = 'libft.a'  # Cible du fichier à surveiller
    make_command = 'make'  # Commande à exécuter
    if not os.path.exists(target):
        print("Erreur: Le fichier cible 'libft.a' n'existe pas.")
        print("Veuillez exécuter le script dans le répertoire contenant votre Makefile.")
    else:
        check_relinking(target, make_command)
    make_command = 'make bonus'  # Commande à exécuter
    if not os.path.exists(target):
        print("Erreur: Le fichier cible 'libft.a' n'existe pas.")
        print("Veuillez exécuter le script dans le répertoire contenant votre Makefile.")
    else:
        check_relinking(target, make_command)
