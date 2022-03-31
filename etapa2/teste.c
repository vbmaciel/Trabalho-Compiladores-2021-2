

float valor, valorinicial, valorfinal;

valorinicial = valor;
printf("Valor inicial: %f\n", valorinicial);

scanf("%d", valor);
valor = valor + (valor*0.15);
valor = valor - (valor*0.08);
valorfinal = valor;

printf("Valor final: %f\n", valorfinal);
printf("%f / %f = %f\n", valorinicial, valorfinal, (valorinicial / valorfinal));
