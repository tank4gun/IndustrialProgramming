import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(host="rabbitmq"))
channel = connection.channel()
channel.queue_declare(queue='hello')

print("Please, type your message")
input_string = input()

channel.basic_publish(exchange='', routing_key='hello', body=input_string)

print("Your message was sent to queue")

connection.close()
