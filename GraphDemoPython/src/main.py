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
        node3 = Node(self.widget)
        edge1 = Edge(node1, node2, self.widget)
        edge2 = Edge(node2, node3, self.widget)
        edge3 = Edge(node3, node1, self.widget)
        node1.setPos(-100, -0)
        node2.setPos(100, -0)
        node3.setPos(0, -100)
        edge1.add_ellipse_animation(Qt.black)
        edge2.add_ellipse_animation(Qt.red)
        edge3.add_ellipse_animation(Qt.blue)
        self.widget.scene().addItem(node1)
        self.widget.scene().addItem(node2)
        self.widget.scene().addItem(node3)
        self.widget.scene().addItem(edge1)
        self.widget.scene().addItem(edge2)
        self.widget.scene().addItem(edge3)

    def keyPressEvent(self, event: QKeyEvent):
        self.widget.keyPressEvent(event)


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())




