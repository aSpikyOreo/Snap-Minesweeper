from flask import Flask
 
app = Flask(__name__)
 


#POST
@app.route('/hello')
def hello():
 if()
    return "hello from the M5Stack!"


#GET 
@app.route('/helloesp')
def helloHandler():
    return 'Hello M5Stack, from Flask'
 

app.run(host='192.168.43.75', port= 8090)