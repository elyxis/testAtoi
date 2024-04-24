import re
import os

def extract_function_prototypes(header_file):
    # Regex améliorée pour gérer les espaces variables
    prototype_pattern = re.compile(r'\b(\w+\s*[*\s]+)\s*(\w+)\s*\(\s*([^)]*)\s*\)\s*;')
    with open(header_file, 'r') as file:
        content = file.read()
    return prototype_pattern.findall(content)

def find_function_declaration(c_file, function_name):
    # Adaptation pour ignorer les espaces multiples
    function_pattern = re.compile(r'\b(\w+\s*[*\s]+)\s*' + re.escape(function_name) + r'\s*\(\s*([^)]*)\s*\)\s*{')
    with open(c_file, 'r') as file:
        content = file.read()
    matches = function_pattern.findall(content)
    return matches[0] if matches else None

def format_function_name(function_name):
    # Nettoyer les noms de fonction en supprimant les astérisques
    return function_name.replace('*', '').strip()

def append_prototype_to_file(c_file, prototype):
    # Ajouter le prototype au fichier .c
    with open(c_file, 'a') as file:
        file.write('\n// Prototype added for verification\n')
        file.write(prototype + '\n')

def verify_prototypes_with_declarations(header_file):
    prototypes = extract_function_prototypes(header_file)
    results = []
    
    for return_type, function_name, args in prototypes:
        clean_function_name = format_function_name(function_name)
        if clean_function_name.startswith('ft_lst'):
            c_file = f'{clean_function_name}_bonus.c'
        else:
            c_file = f'{clean_function_name}.c'

        prototype = f"{return_type.strip()} {clean_function_name}({args.strip()});"
        if os.path.exists(c_file):
            declaration = find_function_declaration(c_file, clean_function_name)
            if declaration:
                decl_return_type, decl_args = declaration
                args_match = ' '.join(args.split()) == ' '.join(decl_args.split())
                return_type_match = ' '.join(return_type.split()) == ' '.join(decl_return_type.split())
                if not (return_type_match and args_match):
                    #####append_prototype_to_file(c_file, prototype)
                    results.append((clean_function_name, False))
                else:
                    results.append((clean_function_name, True))
            else:
                #####append_prototype_to_file(c_file, prototype)
                results.append((clean_function_name, False))
        else:
            results.append((clean_function_name, False))
    
    return results

# Utiliser la fonction pour vérifier les prototypes dans un fichier d'en-tête
header_path = 'libft.h'  # Remplacez par le chemin de votre fichier .h
verification_results = verify_prototypes_with_declarations(header_path)
for function_name, is_match in verification_results:
    if not is_match:
        print(f"Function '{function_name}': Match - {is_match}")
