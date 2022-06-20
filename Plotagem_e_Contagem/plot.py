import matplotlib.pyplot as plt
a = []
b = []
c = []
f = open("contagem.txt", "r")
for x in range(14999):
    num = f.readline()
    num = num.replace('\t', ' ', 8)
    num = num.replace('\n', '', 1)
    numbs = list(num.split())
    
    a.append(int(numbs.pop()))
    b.append(int(numbs.pop()))
    c.append(int(numbs.pop()))
    numbs = []

plt.plot(a, b)
plt.plot(a, c)
ax = plt.gca()
ax.set_ylim([0,300000])
plt.title("Comparação: Bubble-Sort(azul) vs Quick-Sort(laranja)")
plt.ylabel('NÚMERO DE COMPARAÇÕES')
plt.xlabel('TAMANHO DO ARRAY(n)')
plt.show()