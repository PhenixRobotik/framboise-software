#!/usr/bin/env python3

import os

gui_directory = os.path.dirname(os.path.realpath(__file__))
interface_file = os.path.join(gui_directory, "interface.glade")

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class Handler:
    def onDestroy(self, *args):
        Gtk.main_quit()

    def onButtonPressed(self, button):
        print("Hello World!")

builder = Gtk.Builder()
builder.add_from_file(interface_file)
builder.connect_signals(Handler())

window = builder.get_object("window1")
window.fullscreen()
window.show_all()

Gtk.main()
