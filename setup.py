#!/usr/bin/env python3
import os

langs = {
    'python': 'py', 
    'java': 'java', 
    'javascript': 'js',
    'cpp': 'cpp',
    'csharp': 'cs',
    'rust': 'rs',
    'ruby': 'rb',
    'r': 'r'
}

for lang, extension in langs.items():
    for year in range(2015, 2022):
        for day in range(1, 26):
            dir = f'./{lang}/{year}/day{day}'
            if not os.path.exists(dir):
                    os.makedirs(dir)
            for exten in (extension, 'in', 'test'):
                file = f'{dir}/day{day}.{exten}'
                print(file)
                if not os.path.exists(file):
                    open(file, 'w').close()
                
                


