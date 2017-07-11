# suma.s: Sumar los elementos de una lista
#         llamando a función, pasando argumentos mediante registros
#         retorna: código retorno 0, comprobar suma en %eax mediante gdb/ddd

# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista:
	.int 0x1, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000,0xffffffff
 # ejemplos binario 0b / hex 0x
longlista:
	.int (.-lista)/4 # .= contador posiciones. Aritmética de etiquetas.
resultado:
	.quad -1 # 4B a FF para notar cuándo se modifica cada byte
formato:
	.string "%llu / 0x%llx\n"

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
	.global _start # PROGRAMA PRINCIPAL - se puede abreviar de esta forma
	.extern printf # busca printf fuera de este fichero

_start:

	mov $lista, %ebx    # dirección del array lista
	mov longlista, %ecx # número de elementos a sumar
	call suma           # llamar suma(&lista, longlista);
	mov %eax,resultado  # salvar resultado
	mov %edx,resultado+4 

	pushl resultado+4      # apila resultado
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
	xor %eax, %eax # poner a 0 acumulador
	xor %esi, %esi # poner a 0 índice
	xor %edx, %edx # poner el bit de acarreo a 0
bucle:
	add (%ebx,%esi,4), %eax # acumular i-ésimo elemento
	adc $0,%edx		# acumular el acarreo 
	inc %esi                # incrementar índice
	cmp %esi,%ecx           # comparar con longitud
	jne bucle               # si no iguales, seguir acumulando
	ret

