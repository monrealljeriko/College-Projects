
import sys, random
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication, QMainWindow
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import QMessageBox

from tinydb import TinyDB, Query

	#codes for login window
class LoginWindow(QMainWindow):

	def __init__(self):
		super(LoginWindow, self).__init__()
		loadUi("loginWindow.ui",self)
		# self.password.setEchoMode(QtWidgets.QLineEdit.Password)
		self.signUpBtn.clicked.connect(lambda: Button.buttonAction("SignUp"))			#connects to signup window
		self.logInBtn.clicked.connect(self.authenticate)

	def authenticate(self):
		loginUsername = self.logInUserName.text()
		loginPassword = self.logInPass.text()

		userDB = TinyDB('UserDB.json')
		checkDB = Query()
		temp = userDB.search(checkDB.user == loginUsername)

		if loginUsername == "": 
			msg = QMessageBox()
			msg.setIcon(QMessageBox.Critical)
			msg.setText("Username empty!")
			msg.setWindowTitle("Missing")
			msg.exec_()
		elif loginPassword == "":
			msg = QMessageBox()
			msg.setIcon(QMessageBox.Critical)
			msg.setText("Password empty!")
			msg.setWindowTitle("Missing")
			msg.exec_()
		
		elif loginUsername != "admin":
			checkUser = [idx['user'] for idx in temp][0]
			checkPass = [idx['pass'] for idx in temp][0]
			
			if (checkUser == loginUsername) and (checkPass == loginPassword):
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Information)
				msg.setText("Successfully Login!")
				msg.setWindowTitle("Success")
				msg.exec_()
				currentUserID = [idx['userID'] for idx in temp][0]
				passUser.userID = currentUserID
				Button.buttonAction("UserMainWindow")
			else:
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Critical)
				msg.setText("Invalid Username or Password!")
				msg.setWindowTitle("Error")
				msg.exec_()
			
		else:
			if (loginUsername == "admin") and (loginPassword == "admin"):
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Information)
				msg.setText("Successfully Login!")
				msg.setWindowTitle("Success")
				msg.exec_()
				Button.buttonAction("AdminWindow")
			else:
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Critical)
				msg.setText("Invalid Username or Password!")
				msg.setWindowTitle("Error")
				msg.exec_()

class AdminWindow(QDialog):
	def __init__(self):
		super(AdminWindow, self).__init__()
		loadUi("AdminWindow.ui", self)

		self.logOutBtn.clicked.connect(lambda: Button.buttonAction("LoginWindow"))
		self.UpdateBtn.clicked.connect(self.update)

		self.deliveryLogTable.setColumnWidth(0, 264)
		self.deliveryLogTable.setColumnWidth(1, 264)

		loadDB = TinyDB("Database.json")
		row = 0
		self.deliveryLogTable.setRowCount(len(loadDB))

		for item in loadDB:
			self.deliveryLogTable.setItem(row, 0, QtWidgets.QTableWidgetItem(str(item["id"])))
			self.deliveryLogTable.setItem(row, 1, QtWidgets.QTableWidgetItem(str(item["Status"])))
			row = row + 1

	def update(self):
		dataBase = TinyDB("Database.json")
		searchUser = Query()

		dataBase.update({'Status': "Delivered"}, searchUser.id == int(self.refNoInput.text()))

		row = 0
		self.deliveryLogTable.setRowCount(len(dataBase))

		for item in dataBase:
			self.deliveryLogTable.setItem(row, 0, QtWidgets.QTableWidgetItem(str(item["id"])))
			self.deliveryLogTable.setItem(row, 1, QtWidgets.QTableWidgetItem(str(item["Status"])))
			row = row + 1


#codes for signup window
userID = 243514

class SignUp(QDialog):
	def __init__(self):
		super(SignUp, self).__init__()
		loadUi("signUp.ui",self)
		self.createaAccBtn.clicked.connect(self.checkCredentials)	#calls fucntion that returns to login window
		self.backBtn.clicked.connect(lambda: Button.buttonAction("LoginWindow"))

	def checkCredentials(self):
		user = self.signUpUser.text()
		password = self.signUpPass.text()
		repass = self.signUpRePass.text()

		if user == "" or password == "":
			msg = QMessageBox()
			msg.setIcon(QMessageBox.Information)
			msg.setText("Enter Username or Password!")
			msg.setWindowTitle("Missing")
			msg.exec_()
		else:
			if password == repass:
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Information)
				msg.setText("Successfully Created!")
				msg.setWindowTitle("Success")
				msg.exec_()
				userDB = TinyDB('UserDB.json')
				global userID
				userID = userID + random.randint(1, 100)
				temp_dict = {"userID": userID , "user": user, "pass": password}
				userDB.insert(temp_dict)
				Button.buttonAction("LoginWindow")
			else:
				msg = QMessageBox()
				msg.setIcon(QMessageBox.Critical)
				msg.setText("Password don't match")
				msg.setWindowTitle("Error")
				msg.exec_()

class UserMainWindow(QDialog):

	def __init__(self):
		super(UserMainWindow, self).__init__()
		loadUi('ClientWindow.ui', self)
		self.createArrBtn.clicked.connect(lambda: Button.buttonAction("CreateArrangement"))
		self.editArrBtn.clicked.connect(lambda: Button.buttonAction("EditArrangement"))
		self.checkStatusBtn.clicked.connect(lambda: Button.buttonAction("CheckStatus"))
		self.logOutBtn.clicked.connect(lambda: Button.buttonAction("LoginWindow"))


class CreateArrangement(QDialog):

	def __init__(self):
		super(CreateArrangement, self).__init__()
		loadUi('CreateArr.ui', self)
		self.cancelBtn.clicked.connect(lambda: Button.buttonAction("UserMainWindow"))
		self.confirmBtn.clicked.connect(self.passValue)


	def passValue(self):
		self.subFee = 0.00		

		if self.courier.currentText() == "J&T EXPRESS":
			if self.parcelWeight.currentText() == "0.1KG - 1KG":
				self.subFee = 150.00
			elif self.parcelWeight.currentText() == "1KG - 3KG":
				self.subFee = 215.00
			elif self.parcelWeight.currentText() == "3KG+":
				self.subFee = 350.00

		elif self.courier.currentText() == "JRS EXPRESS":
			if self.parcelWeight.currentText() == "0.1KG - 1KG":
				self.subFee = 175.00
			elif self.parcelWeight.currentText() == "1KG - 3KG":
				self.subFee = 300.00
			elif self.parcelWeight.currentText() == "3KG+":
				self.subFee = 500.00

		elif self.courier.currentText() == "NINJA VAN":
			if self.parcelWeight.currentText() == "0.1KG - 1KG":
				self.subFee = 120.00
			elif self.parcelWeight.currentText() == "1KG - 3KG":
				self.subFee = 180.00
			elif self.parcelWeight.currentText() == "3KG+":
				self.subFee = 275.00

		subtotal = self.subFee * self.parcelQuantity.value()
		self.total = subtotal + 125.00
		dataHold.holdData(self.sNameInput.text(), self.sContactInput.text(), self.rNameInput.text(), self.rContactInput.text(), self.parcelWeight.currentText(), self.parcelQuantity.text(), self.courier.currentText(), self.destinationInput.text(), self.pickupInput.text(), subtotal, self.total)
		Button.buttonAction("Payment")


class Payment(QDialog):

	def __init__(self):
		super(Payment, self).__init__()
		loadUi('CreateArrPayment.ui', self)
		tempDB = TinyDB("temp.json")
		temp = tempDB.all()
		self.showSubTotal.setText(str(temp[0]['SubTotal']))
		self.showTotal.setText(str(temp[0]['Total']))
		self.cancelBtn.clicked.connect(self.cancelButton)
		self.confirmBtn.clicked.connect(self.StoreData)
		self.doneBtn.hide()

	def StoreData(self):
		tempDB = TinyDB("temp.json")
		temp = tempDB.all()

		DbID = 257983
		DbID = DbID + random.randint(1, 200)

		storeData.sendToDB(passUser.userID, DbID, temp[0]['SenderName'], temp[0]['SenderContact'], temp[0]['ReceiverName'], temp[0]['ReceiverContact'], temp[0]['ParcelWeight'], temp[0]['ParcelQuantity'], temp[0]['Courier'], temp[0]['Destination'], temp[0]['Pickup'], temp[0]['Total'])
		self.refNoShow.setText(str(DbID))
		self.doneBtn.show()
		self.doneBtn.clicked.connect(lambda: Button.buttonAction("UserMainWindow"))
		tempDB.truncate()

	def cancelButton(self):
		tempDB = TinyDB("temp.json")
		tempDB.truncate()
		Button.buttonAction("CreateArrangement")


class EditArrangement(QDialog):
	def __init__(self):
		super(EditArrangement, self).__init__()
		loadUi('editArr.ui', self)
		self.cancelArrBtn.clicked.connect(self.cancelArrangement)
		self.backBtn.clicked.connect(lambda: Button.buttonAction("UserMainWindow"))

		self.currentArrangements.setColumnWidth(0, 264)
		self.currentArrangements.setColumnWidth(1, 264)

		loadDB = TinyDB("Database.json")
		searchItem = Query()
		temp = loadDB.search(searchItem.UserID == passUser.userID)

		row = 0
		self.currentArrangements.setRowCount(len(temp))

		for item in temp:
			self.currentArrangements.setItem(row, 0, QtWidgets.QTableWidgetItem(str(item["id"])))
			self.currentArrangements.setItem(row, 1, QtWidgets.QTableWidgetItem(str(item["Status"])))
			row = row + 1

	def cancelArrangement(self):
		dataBase = TinyDB("Database.json")
		searchUser = Query()
		
		dataBase.update({'Status': "Cancelled"}, searchUser.id == int(self.refNoInput.text()))
		
		temp = dataBase.search(searchUser.UserID == passUser.userID)

		row = 0
		self.currentArrangements.setRowCount(len(temp))

		for item in temp:
			self.currentArrangements.setItem(row, 0, QtWidgets.QTableWidgetItem(str(item["id"])))
			self.currentArrangements.setItem(row, 1, QtWidgets.QTableWidgetItem(str(item["Status"])))
			row = row + 1


class CheckStatus(QDialog):
	def __init__(self):
		super(CheckStatus, self).__init__()
		loadUi('CheckStatus.ui', self)
		self.checkStatusBtn.clicked.connect(self.Check)
		self.cancelBtn.clicked.connect(lambda: Button.buttonAction("UserMainWindow"))

	def Check(self):
		dataBase = TinyDB("Database.json")
		searchUser = Query()
		temp = dataBase.search(searchUser.id == int(self.refNoInput.text()))
		self.statusShow.setText([item['Status'] for item in temp][0])

class Button:
	def buttonAction(name_func):
		func_name = eval(name_func + "()")
		widget.addWidget(func_name)
		widget.setCurrentIndex(widget.currentIndex()+1)


class dataHold:
	def holdData(sName, sContact, rName, rContact, pWeight, pQuantity, courier, destination, pickup, subtotal, total):
		tempDB = TinyDB("temp.json")
		temp_dict = {"SenderName": sName, "SenderContact": sContact, "ReceiverName": rName, "ReceiverContact": rContact, "ParcelWeight": pWeight, "ParcelQuantity":pQuantity, "Courier": courier, "Destination": destination, "Pickup":pickup, "SubTotal": subtotal, "Total": total}
		tempDB.insert(temp_dict)


class storeData:
	def sendToDB(userID, refID, sName, sContact, rName, rContact, pWeight, pQuantity, courier, destination, pickup, total):
		dataBase = TinyDB("Database.json")
		dataBase.insert({"UserID": userID, "id": refID, "SenderName": sName, "SenderContact": sContact, "ReceiverName": rName, "ReceiverContact": rContact, "ParcelWeight": pWeight, "ParcelQuantity": pQuantity, "Courier": courier, "Destination": destination, "Pickup":pickup, "Total": total, "Status": "Ongoing Delivery"})


class passUser:
	def __init__(self):
		passUser.userID = userID

	def getUserID(self):
		return passUser.userID


if __name__ == "__main__":
	import sys
	app = QtWidgets.QApplication(sys.argv)
	mainwindow = LoginWindow()
	widget = QtWidgets.QStackedWidget()
	widget.addWidget(mainwindow)
	widget.setFixedWidth(590)
	widget.setFixedHeight(870)
	widget.show()
	sys.exit(app.exec_())