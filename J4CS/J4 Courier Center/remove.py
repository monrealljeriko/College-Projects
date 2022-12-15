from tinydb import TinyDB, Query

db=TinyDB('UserDB.json')
db.truncate()