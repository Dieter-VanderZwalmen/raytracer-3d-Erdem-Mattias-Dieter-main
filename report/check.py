import json
import sys


duplicatable = { "Scripting", "Mesh Optimizer" }
mandatory = { "Mesh Optimizer" }


with open('report.json', encoding='utf-8') as file:
    data = json.load(file)


with open('weights.json', encoding='utf-8') as file:
    weights = json.load(file)


def duplicates_allowed(extension):
    return extension in duplicatable


def name(member):
    fname = member['firstName']
    lname = member['lastName']
    return f"{fname} {lname}"


extensions_by_member = { name(member): member['extensions'] for member in data['team-members'] }


# Check for duplicates
for member, extensions in extensions_by_member.items():
    if len(extensions) != len(set(extensions)):
        print(f'{member} has duplicate extensions!')

made_extensions = [ extension for extensions in extensions_by_member.values()
                              for extension in extensions
                              if not duplicates_allowed(extension) ]

if len(made_extensions) != len(set(made_extensions)):
    print(f'Multiple members made the same extension!')


# Check for mandatory
for member, extensions in extensions_by_member.items():
    if not all(m in extensions for m in mandatory):
        print(f'{member} is lacking mandatory extensions!')


# Check for nonexisting extensions
for member, extensions in extensions_by_member.items():
    for extension in extensions:
        if extension not in weights:
            print(f'{member} has made unknown extension {extension}')


# Sum weights
for member, extensions in extensions_by_member.items():
    total = sum(weights.get(extension, 0) for extension in extensions)
    print(f'{member} has accumulated {total} weight points')
