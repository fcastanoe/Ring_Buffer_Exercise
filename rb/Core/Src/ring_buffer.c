#include "ring_buffer.h"

#define capacity (10)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full;

/**
 * @brief Esta función reinicia el buffer circular.
 *
 * @retval Ninguno
 */
void ring_buffer_reset(void)
{
    head_ptr = 0;
    tail_ptr = 0;
    is_full = 0;
}

/**
 * @brief Esta función calcula los datos disponibles en el buffer.
 *
 * @retval size: cantidad de datos disponibles.
 */
uint8_t ring_buffer_size(void)
{
    if (is_full) {
        return capacity;
    } else if (head_ptr >= tail_ptr) {
        return head_ptr - tail_ptr;
    } else {
        return capacity - (tail_ptr - head_ptr);
    }
}

/**
 * @brief Esta función verifica si el buffer está lleno.
 *
 * @retval 1: buffer lleno, 0: buffer no lleno.
 */
uint8_t ring_buffer_is_full(void)
{
    return is_full;
}

/**
 * @brief Esta función verifica si el buffer está vacío.
 *
 * @retval 1: buffer vacío, 0: buffer no vacío.
 */
uint8_t ring_buffer_is_empty(void)
{
    return (!is_full && (head_ptr == tail_ptr));
}


/**
 * @brief Esta funcion escribe un dato en el buffer circular
 *
 * @param data: el dato que se va a escribir
 *
 * @retval Ninguno
 */
void ring_buffer_write(uint8_t data)
{
    ring_buffer[head_ptr] = data;
    head_ptr++;

    if (head_ptr >= capacity) {
        head_ptr = 0;
    }

    if (is_full) {
        tail_ptr++;
        if (tail_ptr >= capacity) {
            tail_ptr = 0;
        }
    }

    if (head_ptr == tail_ptr) {
        is_full = 1;
    }
}


/**
 * @brief Esta funcion lee un dato del buffer circular
 *
 * @param data: la direccion de donde se va a escribir el dato
 *
 * @retval 1: hay datos disponibles, 0: no hay datos
 */
uint8_t ring_buffer_read(uint8_t *data) // 0x20
{
	if ((is_full != 0) || (head_ptr != tail_ptr)) { // data available
		*data = ring_buffer[tail_ptr]; // add: 0x20, val: buffer
		tail_ptr = tail_ptr + 1;
		if (tail_ptr >= capacity) {
			tail_ptr = 0;
		}
		is_full = 0;

		return 1; // buffer con datos
	}
	return 0; // buffer vacio
}
