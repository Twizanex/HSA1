"""
This module handles all data visualization live and post.
    robotplot is for plot properties and can be shared between live and static plots.
    liveplotter can be given data in real time.
    staticplotter is for analyzing data in post using log files.
"""

from .liveplotter import LivePlotter
from .staticplotter import StaticPlotter
from .collection import RobotPlotCollection
from .plot import RobotPlot
