# a) Matriz P de transição de estados
P = [0.95 0.05; 0.001 0.999];

# b) Probabilidade do 4 bit ser incorreto
p0 = [0 1];

p4 = p0*P^4;
# p4(1) = 0.0037043 => 0.37% -> bit incorreto

# c) Longa sequência de bits percentual de bits recebidos incorretamente 
pi_inf = p0*P^inf;
# pi_inf(1) = 0.019608 => 1.966% -> bit incorreto
