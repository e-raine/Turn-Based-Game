user_input = int(input("Input a Positive number : "))

if user_input <= 0:
    print("Invalid input. Re-run the code.")
else:
    if (user_input == 1):
        answer = "is Not a Prime Number"
    else:
        answer = "is a Prime Number"
        i = 2
        while i <= user_input/2 :
            rem = user_input % i 
            if rem != 0:
                i += 1
            else:
                answer = "is Not a Prime Number"
                break
    print("The number "+ str(user_input), answer)