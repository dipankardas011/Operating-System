/**
 * 
 * @author Dipankar Das
 * @date dd-mm-yyy
 * @version 0.xx.xx
 * 
 */


/**
 * @Stack
 * ==========
 * | 0x200  |
 * | 0x196  | address is reducing when we are pushing
 * | 0x192  | .....
 * ((((TOP))))
 * 
 * During the pop() we will be adding 
 * 
 * {PUSH}
 * MOV (SP)-, NEW_DATA
 * 
 * {POP}
 * MOV SP, DATA
 * MOV +(SP)
 * 
 * BOOK
 * {PUSH}
 * mov DATA, -(sp) [ prefix ]
 * 
 * {POP}
 * mov (sp)+, data [ postfix ]
 * in pop we get the data then decrement
 */
