import pika
import psycopg2

connection = pika.BlockingConnection(pika.ConnectionParameters(host='rabbitmq'))
channel = connection.channel()
channel.queue_declare(queue='hello')


def insert_in_db(new_string):
    try:
        cursor.execute("INSERT INTO strings_input VALUES (%s);", [new_string.decode('UTF-8')])
        cursor.execute("SELECT * from strings_input;")
        rows = cursor.fetchall()
        print(rows)
    except Exception as e:
        print("Uh oh, can't connect. Invalid dbname, user or password")
        print(e)


def callback(ch, method, properties, body):
    insert_in_db(body)
    print(" [x] Received ", body.decode('UTF-8'))

channel.basic_consume(callback, queue='hello', no_ack=True)
print(' [*] Wainting for messages. To exit press CTRL+C')
connect_str = "dbname='postgres' user='postgres' host='database' password='mysecretpassword'"
conn = psycopg2.connect(connect_str)
cursor = conn.cursor()
conn.set_isolation_level(0)
cursor.execute("DROP TABLE IF EXISTS strings_input;")
cursor.execute("""CREATE TABLE strings_input (string varchar);""")
channel.start_consuming()

