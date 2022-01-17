price=int(input("Enter Product 1 Price"))
price1=int(input("Enter Product 2 Price"))
price2=int(input("Enter Product 3 Price"))
total= price+price1+price2
discount=total*10/100
final=total-discount
print(final,"this is the amount after the discount of 10%")
