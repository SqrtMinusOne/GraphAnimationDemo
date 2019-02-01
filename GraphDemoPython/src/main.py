from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QKeyEvent
from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow

from edge import Edge
from mainwindow import Ui_MainWindow
from graphwidget import GraphWidget
from node import Node


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        self.widget = GraphWidget(self)
        self.mainGraphicsView.setViewport(self.widget)
        node1 = Node(self.widget)
        node2 = Node(self.widget)
        edge = Edge(node1, node2, self.widget)
        edge.add_ellipse_animation(Qt.black)
        node2.setPos(100, 100)
        self.widget.scene().addItem(node1)
        self.widget.scene().addItem(node2)
        self.widget.scene().addItem(edge)

    def keyPressEvent(self, event: QKeyEvent):
        self.widget.keyPressEvent(event)


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())




