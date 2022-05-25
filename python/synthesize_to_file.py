import pyttsx3
import sys

text = str(sys.argv[0])
rate = int(sys.argv[1])
id = int(sys.argv[2])
file = str(sys.argv[3])

engine = pyttsx3.init()
engine.setProperty('rate', rate)
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[id].id)

engine.save_to_file(text, file)
engine.runAndWait()