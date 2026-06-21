# Generates cpp.json with snippets for VSCode
import os
import json
import sys

snippets = {}

for root, dirs, files in os.walk('.'):
    if root == '.' or '.git' in root:
        continue

    for filename in files:
        name, extension = os.path.splitext(filename)

        # chỉ lấy .cpp
        if extension != '.cpp':
            continue

        # tránh trùng snippet
        if name in snippets:
            print(f'error: duplicate snippet {name}', file=sys.stderr)
            exit(0)

        path = os.path.join(root, filename)

        try:
            with open(path, 'r', encoding='utf-8') as f:
                body = [line.rstrip('\n') for line in f.readlines()]
        except Exception as e:
            print(f'error reading {path}: {e}', file=sys.stderr)
            continue

        snippet = {
            "prefix": name,
            "body": body,
            "description": name
        }

        snippets[name] = snippet

        print(f'generated snippet {name}', file=sys.stderr)

with open('cpp.json', 'w', encoding='utf-8') as f:
    json.dump(snippets, f, indent=2, ensure_ascii=False)

print('done', file=sys.stderr)