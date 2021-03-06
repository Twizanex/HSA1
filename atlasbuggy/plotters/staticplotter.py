"""
Contains the static plotter class. This class plots data retrieved from a log file
according to properties defined in RobotPlot.
"""

from ..plotters.baseplotter import BasePlotter
from ..plotters.plot import RobotPlot
from ..plotters.collection import RobotPlotCollection
from ..datastream import DataStream


class StaticPlotter(BasePlotter, DataStream):
    def __init__(self, num_columns, *robot_plots, enabled=True, name=None, log_level=None,
                 draw_legend=True, legend_args=None, matplotlib_events=None):
        """
        :param num_columns: Configure how the subplots are arranged
        :param robot_plots: RobotPlot or RobotPlotCollection instances. Each one will be a subplot
        :param legend_args: dictionary of arguments to pass to plt.legend
        """
        BasePlotter.__init__(
            self, num_columns, legend_args, draw_legend, matplotlib_events, enabled, *robot_plots
        )

        DataStream.__init__(self, enabled, name, log_level)

        if self.enabled:
            for plot in self.robot_plots:
                self._create_lines(plot)
            self.init_legend()

    def update_collection(self, plot):
        if plot.name not in self.lines:
            self.lines[plot.name] = {}

        if plot.flat:
            for subplot in plot.plots:
                self.lines[plot.name][subplot.name] = None
        else:
            for subplot in plot.plots:
                self.lines[plot.name][subplot.name] = None

    def _create_lines(self, plot):
        if isinstance(plot, RobotPlot):
            if plot.flat:
                self.lines[plot.name] = None
            else:
                self.lines[plot.name] = None
        elif isinstance(plot, RobotPlotCollection):
            self.update_collection(plot)

    def add_plots(self, *robot_plots, num_columns=None):
        self.add_subplots(*robot_plots, num_columns=num_columns)
        for plot in self.robot_plots:
            self._create_lines(plot)

    def plot(self, show=True):
        """
        To be called in a simulator's close function after all data has been compiled.
        Call show once after all plots are done
        :return: None
        """
        if not self.enabled:
            return

        for plot in self.robot_plots:
            if isinstance(plot, RobotPlot):
                if plot.flat:
                    self.lines[plot.name] = self.axes[plot.name].plot(
                        plot.data[0], plot.data[1], **plot.properties)[0]
                else:
                    self.lines[plot.name] = self.axes[plot.name].plot(
                        plot.data[0], plot.data[1], plot.data[2], **plot.properties)[0]
            elif isinstance(plot, RobotPlotCollection):
                if plot.flat:
                    for subplot in plot.plots:
                        self.lines[plot.name][subplot.name] = self.axes[plot.name].plot(
                            subplot.data[0], subplot.data[1], **subplot.properties)[0]
                else:
                    for subplot in plot.plots:
                        self.lines[plot.name][subplot.name] = self.axes[plot.name].plot(
                            subplot.data[0], subplot.data[1], subplot.data[2], **subplot.properties)[0]
        for plot in self.robot_plots:
            if plot.ranges_set():
                if plot.flat:
                    self.axes[plot.name].set_xlim(plot.x_range)
                    self.axes[plot.name].set_ylim(plot.y_range)
                else:
                    self.axes[plot.name].set_xlim3d(plot.x_range)
                    self.axes[plot.name].set_ylim3d(plot.y_range)
                    self.axes[plot.name].set_zlim3d(plot.z_range)

        if show:
            self.plt.show()

    def stopped(self):
        self.plot()
