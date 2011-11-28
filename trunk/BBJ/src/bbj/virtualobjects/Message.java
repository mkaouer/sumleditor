/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.virtualobjects;

/**
 * Абстрактный класс сообщений.
 * Является суперклассом для сообщений.
 * @version 1.0
 */
abstract public class Message extends UMLObject {

    /* Поля класса. */
    private LifeLine m_sender; /** Линия жизин - отправитель сообщения. */
    private LifeLine m_receiver; /** Линия жизни - приемник сообщения. */
}