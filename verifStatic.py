import re
import os

def remove_comments(content):
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    inline_comments = re.findall(r'//.*', content)
    content = re.sub(r'//.*', '', content)
    return content, inline_comments

def extract_function_prototypes(header_file):
    with open(header_file, 'r') as file:
        content = file.read()
    content, _ = remove_comments(content)
    prototype_pattern = re.compile(r'\b(\w+[*\s]+)(\w+)\(([^)]*)\)\s*;')
    return prototype_pattern.findall(content)

def extract_all_functions(c_file):
    with open(c_file, 'r') as file:
        content = file.read()
    content, inline_comments = remove_comments(content)
    all_functions_pattern = re.compile(r'(\bstatic\b)?\s*(\w+[*\s]+)(\w+)\(([^)]*)\)\s*{')
    functions = all_functions_pattern.findall(content)
    return functions, inline_comments

def format_function_name(function_name):
    return function_name.replace('*', '').strip()

def check_static_functions(c_file, main_function_name):
    all_functions, inline_comments = extract_all_functions(c_file)
    errors = []
    if inline_comments:
        errors.append(f"*** File {c_file} contains inline comments.")
    for is_static, _, function_name, _ in all_functions:
        if format_function_name(function_name) == main_function_name:
            if is_static:
                errors.append(f"*** {c_file}  {function_name} should not be static.")
        else:
            if not is_static:
                errors.append(f"*** {c_file}  {function_name} should be static.")
    return errors

def verify_prototypes_with_declarations(header_file):
    prototypes = extract_function_prototypes(header_file)
    results = []
    
    for return_type, function_name, args in prototypes:
        formatted_function_name = format_function_name(function_name)
        if formatted_function_name.startswith('ft_lst'):
            c_file = f'{formatted_function_name}_bonus.c'
        else:
            c_file = f'{formatted_function_name}.c'

        if os.path.exists(c_file):
            errors = check_static_functions(c_file, formatted_function_name)
            results.extend(errors if errors else [f"All functions in {c_file} are correctly declared."])
        else:
            results.append(f"File {c_file} not found.")
    
    return results

# Utiliser la fonction pour vérifier les prototypes et les déclarations static
header_path = 'libft.h'  # Remplacez par le chemin de votre fichier .h
verification_results = verify_prototypes_with_declarations(header_path)
for result in verification_results:
    print(result)
