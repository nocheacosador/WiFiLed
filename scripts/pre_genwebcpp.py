import os

Import('env')

inFiles = [
    'web\\slider_picker.html',
    'web\\slider.css',
    'web\\main.js',
]

def addFile(file, filePath):
    cpp_variable_name = os.path.basename(filePath).replace('.', '_')
    with open(filePath, 'r') as inFile:
        file.write(f'    const char* {cpp_variable_name} =')
        
        for line in inFile:
            #line = line.replace('\t', '')
            #line = line.replace('    ', '')
            
            line = line.replace('\\', '\\\\')
            line = line.replace('"', '\\"')
            line = line.replace('\n', '\\n')
            
            #if line[-1] == '\n': 
            #    file.write(f'\n        "{line[:-1]}"')
            #else:
            file.write(f'\n        "{line}"')

        file.write('\n        "";\n\n')

with open(os.path.join(env['PROJECT_DIR'], 'src\\WebFiles.cpp'), 'w') as file:
    file.write('namespace WebFiles \n{\n')

    for filePath in inFiles:
        addFile(file, os.path.join(env['PROJECT_DIR'], filePath))

    file.write('};')
