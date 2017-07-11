# suma.s: Sumar los elementos de una lista
#         llamando a función, pasando argumentos mediante registros
#         retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista:
	.int -1,-1,-1,-1 # ejemplos binario 0b / hex 0x
longlista:
	.int (.-lista)/4 # .= contador posiciones. Aritmética de etiquetas.
resultado:
	.quad -1 # 4B a FF para notar cuándo se modifica cada byte
formato:
	.string "%lli / 0x%llx \n"

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
	.global _start # PROGRAMA PRINCIPAL - se puede abreviar de esta forma
	.extern printf # busca printf fuera de este fichero

_start:

	mov $lista, %ebx    # dirección del array lista
	mov longlista, %ecx # número de elementos a sumar
	call suma           # llamar suma(&lista, longlista);
	cltd  
	mov %eax,resultado  # salvar resultado
	mov %edx,resultado+4

	pushl resultado+4     # apila resultado
	pushl resultado      # apila resultado

	pushl resultado+4      # apila resultado
	pushl resultado      # apila resultado

	pushl $formato       # apila formato
	call printf         # llamada a función printf(&formato, resultado)
	add $12, %esp       # dejar pila intacta

	# void _exit(int status);
	mov $1, %eax # exit: servicio 1 kernel Linux
	mov $0, %ebx # status: código a retornar (0=OK)
	int $0x80    # llamar _exit(0);

# SUBRUTINA: suma(int* lista, int longlista);
#            entrada: 1) %ebx = dirección inicio array
#                     2) %ecx = número de elementos a sumar
#            salida:     %eax = resultado de la suma

suma:
	xor %edi, %edi # poner acumulador1 a 0
	xor %ebp, %ebp # poner acumulador2 a 0
	xor %eax, %eax # poner resultado a 0
	xor %esi, %esi # poner a 0 índice
	xor %edx, %edx # poner a 0 el acarreo
bucle:
	mov (%ebx,%esi,4),%edi	# La idea inicial era pasar numero a %eax pero para usar menos registros lo he pasado a edi y lo acumulo en eax asi me ahorro los mov que estan comentados 
	cltd  	# pasar de 2 words a 4 words se queda en los registros eax:edx
	addl %edi,%eax	# acumular i-ésimo elemento
	adc $0,%edx	# acumular el acarreo	
	inc %esi                # incrementar índice
	cmp %esi,%ecx           # comparar con longitud
	jne bucle               # si no iguales, seguir acumulando
	#movl %edi,%eax #
	#movl %ebp,%edx
	ret

