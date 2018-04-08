f = open('messageInput.txt', 'r')

wordBytes = f.read()

f.close()

wordBytes = wordBytes.split(' ')

for i in range(len(wordBytes)):

    wordBytes[i] = wordBytes[i].strip()


print(wordBytes)

f = open('messageOutput.txt', 'w')

columnIndex = 0

for wb in wordBytes:
    f.write('0x' + wb)

    columnIndex += 1
    
    if columnIndex == 12:
        f.write(',\n')
        columnIndex = 0
    else:
        f.write(', ')

f.close()
    
