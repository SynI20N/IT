%numbers
a = 5.4
b = 10
a + b
a - b
a / b

%matrices
c = [1,2,3;4,5,6]
d = [2,3;1,4;5,6]
c * d
e = zeros(2,3)
e - c
e = transpose(e)
d = det([1,2;3,4])
rnd = rand(5,5)
mgc = magic(5)

%chars
syms x y
(x-y)*(x-y)^2
simplify((x^3-y^3)/(x-y))

%compare
cos(pi/2)
cos(sym(pi/2))
sym('1/2')+sym('1/3')

%compare2
3^45
vpa(3^45)

%plots
x = -4:0.1:4
y = x.^3-x
figure(1)
plot(x, y)

x = -2:0.1:2
y = sin(1./x.^2)
figure(2)
plot(x, y)

figure(3)
fplot(@(x) tan(x/2))
axis([-pi pi -10 10])

x = linspace(-1.5, 1.5)
Y = exp(((x.*(-1)).^2)./2)
y = x.^4-x.^2
figure(4)
plot(x,y,x,Y)

