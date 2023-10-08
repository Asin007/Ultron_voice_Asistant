import speech_recognition as sr   # voice recognition library
from googletrans import Translator
import pyttsx3                    # offline Text to Speech
import datetime                   # to get date and time
import wikipedia                 # to open and perform web tasks
import serial                     # for serial communication
import pywhatkit as kt
import pyjokes

listener = sr.Recognizer()
engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[1].id)

try:
    port = serial.Serial("COM6", 9600) 
    print("Phycial body, connected.")
except:
    print("Unable to connect to my physical body")


def talk(text):
    engine.say(text)
    engine.runAndWait()


def take_command():
    try:
        with sr.Microphone() as source:
            print('listening...')
            voice = listener.listen(source)
            command = listener.recognize_google(voice)
            command = command.lower()
            if 'Ultron' in command:
                command = command.replace('Ultron', '')
                print(command)
    except:
        pass
    return command 

def run_Ultron():
    command = take_command()
    print(command)
    if 'play' in command:
        song = command.replace('play', '')
        talk('playing ' + song)
        kt.playonyt(song)
    elif 'time' in command:
        time = datetime.datetime.now().strftime('%I:%M %p')
        talk('Current time is ' + time)
    elif 'what is ' in command:
        person = command.replace('what is', '')
        info = wikipedia.summary(person, 1)
        print(info)
        talk(info)
    elif 'who is ' in command:
        person = command.replace('who is', '')
        info = wikipedia.summary(person, 1)
        print(info)
        talk(info)    
    elif 'joke' in command:
        talk(pyjokes.get_joke())
    elif 'hi' in command:
        port.write (b'h')  
    elif ' punch' in command:
        port.write(b'p') 
    elif 'look left' in command:
        port.write (b'l')         
    elif 'date' in command:
        talk('sorry, I have a headache')
    elif 'are you single' in command:
        talk('I am in a relationship with wifi')
    elif 'uppercut' in command:
        port.write(b'U')
    elif 'handsup' in command:
        port.write(b'u') 
    elif 'Meassure' in command:
        port.write(b'M')    
        talk(port.write) 
    elif 'Temprature' in command:
        port.write(b'T')
        talk(b'T')          
    if "bye" in command:
        talk('ok bye')
    else:
        talk('Please say the command again.')    
        

# run the app
while True:
    run_Ultron()
