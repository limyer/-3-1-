n = int(input("0이 아닌 숫자를 넣으세요. 끝내려면 0을 입력하세요: "))

for i in range(1, 10) :
    if n == 0 : 
       break
    print(n,'X',i, '=', str(n*i))
