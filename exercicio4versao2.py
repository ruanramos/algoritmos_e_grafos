#Ruan da Fonseca Ramos

def head_to_tail(n):

    currentState = []
    
    
    def busca_prof(currentState):
        
        # visite o vertice v: preciso fazer algo especial?
        if len(currentState) == n:
            shouldPrint = True
            for i in range (0, len(currentState)):
                if currentState[i] != currentState[len(currentState)-1]:
                    if currentState[i][-1] != currentState[i+1][0]:
                        shouldPrint = False
                
            if shouldPrint:
                for i in range (0, len(currentState)):
                    print(currentState[i],)
                return True

        # para cada candidato a ser um vizinho w de v...
        for candidate in strings:
            
            if candidate not in currentState:
                # encontrei um vizinho w

                # expando o estado corrente
                currentState.append(candidate)
                
                # chamo recursivamente
                if busca_prof(currentState):
                    return True
                

                # desfaco a modificacao que tinha sido feita
                currentState.pop()
        
        # Não achei nenhuma solução
        return False
                

    # ----------

    if not busca_prof(currentState):
        print (-1)

strings = []
n = input('')
n = int(n)
for i in range(0, n):
    string = input('')
    strings.append(string)

head_to_tail(n)
