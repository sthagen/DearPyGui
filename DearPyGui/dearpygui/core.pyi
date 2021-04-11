from typing import List, Any, Callable
from dearpygui.core import *

##########################################################
# This file is generated automatically by mvPythonParser #
##########################################################

# ~ Dear PyGui Version: master
def add_about_window(name: str = ..., *, width: int = -1, height: int = -1, x_pos: int = 200, y_pos: int = 200, autosize: bool = False, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True) -> None:
	"""Creates an about window."""
	...

def add_area_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., fill: List[float] = (0, 0, 0, -1), label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_bar_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., weight: float = 1.0, horizontal: bool = False, label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_button(name: str = ..., *, small: bool = False, arrow: bool = False, direction: int = 0, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True, enabled: bool = True) -> None:
	"""Adds a button."""
	...

def add_candle_series(name: str = ..., *, dates: List[float] = ..., opens: List[float] = ..., closes: List[float] = ..., lows: List[float] = ..., highs: List[float] = ..., tooltip: bool = True, bull_color: List[float] = (0, 255, 113, 255), bear_color: List[float] = (218, 13, 79, 255), weight: float = 0.25, label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_checkbox(name: str = ..., *, default_value: int = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', label: str = '', show: bool = True, enabled: bool = True) -> None:
	"""Adds a checkbox widget."""
	...

def add_child(name: str = ..., *, show: bool = True, parent: str = '', before: str = '', width: int = 0, height: int = 0, border: bool = True, autosize_x: bool = False, autosize_y: bool = False, no_scrollbar: bool = False, horizontal_scrollbar: bool = False, menubar: bool = False) -> None:
	"""Adds an embedded child window. Will show scrollbars when items do not fit. Must be followed by a call to end."""
	...

def add_collapsing_header(name: str = ..., *, label: str = '', show: bool = True, parent: str = '', before: str = '', closable: bool = False, default_open: bool = False, open_on_double_click: bool = False, open_on_arrow: bool = False, leaf: bool = False, bullet: bool = False) -> None:
	"""Adds a collapsing header to add items to. Must be closed with the end command."""
	...

def add_color_button(name: str = ..., *, default_value: List[int] = (0, 0, 0, 255), callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', width: int = 0, height: int = 0, show: bool = True, no_alpha: bool = False, no_border: bool = False, no_drag_drop: bool = False, enabled: bool = True) -> None:
	"""Adds a color button."""
	...

def add_color_edit3(name: str = ..., *, default_value: List[int] = (0, 0, 0, 255), callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True, enabled: bool = True, no_alpha: bool = False, no_picker: bool = False, no_options: bool = False, no_small_preview: bool = False, no_inputs: bool = False, no_tooltip: bool = False, no_label: bool = False, no_drag_drop: bool = False, alpha_bar: bool = False, alpha_preview: bool = False, alpha_preview_half: bool = False, display_rgb: bool = False, display_hsv: bool = False, display_hex: bool = False, uint8: bool = False, floats: bool = False, input_rgb: bool = False, input_hsv: bool = False) -> None:
	"""Adds an rgb color editing widget. Click and draging the color square will copy the color to be applied on any other color widget."""
	...

def add_color_edit4(name: str = ..., *, default_value: List[int] = (0, 0, 0, 255), callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True, enabled: bool = True, no_alpha: bool = False, no_picker: bool = False, no_options: bool = False, no_small_preview: bool = False, no_inputs: bool = False, no_tooltip: bool = False, no_label: bool = False, no_drag_drop: bool = False, alpha_bar: bool = False, alpha_preview: bool = False, alpha_preview_half: bool = False, display_rgb: bool = False, display_hsv: bool = False, display_hex: bool = False, uint8: bool = False, floats: bool = False, input_rgb: bool = False, input_hsv: bool = False) -> None:
	"""Adds an rgba color editing widget. Click and draging the color square will copy the color to be applied on any other color widget."""
	...

def add_color_picker3(name: str = ..., *, default_value: List[int] = (0, 0, 0, 255), callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True, enabled: bool = True, no_alpha: bool = False, no_small_preview: bool = False, no_inputs: bool = False, no_tooltip: bool = False, no_label: bool = False, no_side_preview: bool = False, alpha_bar: bool = False, alpha_preview: bool = False, alpha_preview_half: bool = False, display_rgb: bool = False, display_hsv: bool = False, display_hex: bool = False, uint8: bool = False, floats: bool = False, picker_hue_bar: bool = False, picker_hue_wheel: bool = False, input_rgb: bool = False, input_hsv: bool = False) -> None:
	"""Adds an rgb color picking widget. Click and draging the color square will copy the color to be applied on any other color widget. Right Click allows the style of the color picker to be changed."""
	...

def add_color_picker4(name: str = ..., *, default_value: List[int] = (0, 0, 0, 255), callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True, enabled: bool = True, no_alpha: bool = False, no_small_preview: bool = False, no_inputs: bool = False, no_tooltip: bool = False, no_label: bool = False, no_side_preview: bool = False, alpha_bar: bool = False, alpha_preview: bool = False, alpha_preview_half: bool = False, display_rgb: bool = False, display_hsv: bool = False, display_hex: bool = False, uint8: bool = False, floats: bool = False, picker_hue_bar: bool = False, picker_hue_wheel: bool = False, input_rgb: bool = False, input_hsv: bool = False) -> None:
	"""Adds an rgba color picking widget. Click and draging the color square will copy the color to be applied on any other color widget. Right Click allows the style of the color picker to be changed"""
	...

def add_colormap_scale(name: str = ..., *, default_value: int = 0, min_scale: float = 0.0, max_scale: float = 1.0, parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, label: str = '', show: bool = True) -> None:
	"""Adds drag for a single int value. CTRL+Click to directly modify the value."""
	...

def add_combo(name: str = ..., *, items: List[str] = (), default_value: str = '', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, label: str = '', show: bool = True, popup_align_left: bool = False, height_small: bool = False, height_regular: bool = False, height_large: bool = False, height_largest: bool = False, no_arrow_button: bool = False, no_preview: bool = False) -> None:
	"""Adds a combo."""
	...

def add_data_grid(name: str = ..., *, headers: List[str] = ..., callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', width: int = 0, height: int = 200, hide_headers: bool = False, show: bool = True) -> None:
	"""Adds data grid."""
	...

def add_date_picker(name: str = ..., *, default_value: dict = {'month_day': 14, 'year':20, 'month':5}, level: int = 0, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a data selector widget."""
	...

def add_debug_window(name: str = ..., *, width: int = 700, height: int = 500, x_pos: int = 200, y_pos: int = 200, autosize: bool = False, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True) -> None:
	"""Creates a debug window."""
	...

def add_doc_window(name: str = ..., *, width: int = -1, height: int = -1, x_pos: int = 200, y_pos: int = 200, autosize: bool = True, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True) -> None:
	"""Creates a documentation window."""
	...

def add_drag_float(name: str = ..., *, default_value: float = 0.0, speed: float = 1.0, min_value: float = 0.0, max_value: float = 100.0, format: str = '%0.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds drag for a single float value. CTRL+Click to directly modify the value."""
	...

def add_drag_floatx(name: str = ..., *, default_value: List[float] = (0.0, 0.0, 0.0, 0.0), size: int = 4, speed: float = 1.0, min_value: float = 0.0, max_value: float = 100.0, format: str = '%0.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds drag for multiple float values. CTRL+Click to directly modify the value."""
	...

def add_drag_int(name: str = ..., *, default_value: int = 0, speed: float = 1.0, min_value: int = 0, max_value: int = 100, format: str = '%d', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds drag for a single int value. CTRL+Click to directly modify the value."""
	...

def add_drag_intx(name: str = ..., *, default_value: List[float] = (0, 0, 0, 0), size: int = 4, speed: float = 1.0, min_value: int = 0, max_value: int = 100, format: str = '%0.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds drag for multiple int values. CTRL+Click to directly modify the value."""
	...

def add_drag_line(name: str = ..., *, default_value: List[float] = (0.0, 0.0, 0.0, 0.0), label: str = '', source: str = '', color: List[float] = (0, 0, 0, -1), thickness: float = 1.0, show_label: bool = True, vertical: bool = True, callback: Callable = None, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_drag_point(name: str = ..., *, default_value: List[float] = (0.0, 0.0, 0.0, 0.0), label: str = '', source: str = '', color: List[float] = (0, 0, 0, -1), radius: float = 4.0, show_label: bool = True, callback: Callable = None, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_drawing(name: str = ..., *, parent: str = '', before: str = '', width: int = 0, height: int = 0, show: bool = True) -> None:
	"""Adds a drawing widget."""
	...

def add_dummy(name: str = 'dummy', *, width: int = 0, height: int = 0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a spacer or 'dummy' object."""
	...

def add_error_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., negative: List[float] = ..., positive: List[float] = ..., horizontal: bool = False, label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_font(font: str, file: str, size: float = 13.0, glyph_ranges: str = '', *, custom_glyph_chars: List[int] = (), custom_glyph_ranges: Any = List[List[int]], char_remaps: Any = List[List[int]]) -> None:
	"""Adds additional font."""
	...

def add_grid_column(data_grid: str, name: str, column: List[str]) -> None:
	"""Adds a column to the end of a data grid."""
	...

def add_grid_row(data_grid: str, row: List[str]) -> None:
	"""Adds a row to the end of a data grid."""
	...

def add_group(name: str = ..., *, show: bool = True, parent: str = '', before: str = '', width: int = 0, horizontal: bool = False, horizontal_spacing: float = -1) -> None:
	"""Creates a group that other widgets can belong to. The group allows item commands to be issued for all of its members.				Must be closed with the end command."""
	...

def add_heat_series(name: str = ..., *, x: List[float] = ..., rows: int = 1, cols: int = 1, scale_min: float = 0.0, scale_max: float = 1.0, format: str = '%0.1f', bounds_min: List[float] = (0.0, 0.0), bounds_max: List[float] = (1.0, 1.0), label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_hline_series(name: str = ..., *, x: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_image(name: str = ..., *, value: str = ..., tint_color: List[float] = (255, 255, 255, 255), border_color: List[float] = (0, 0, 0, 0), parent: str = '', before: str = '', source: str = '', width: int = 0, height: int = 0, uv_min: List[float] = (0.0, 0.0), uv_max: List[float] = (1.0, 1.0), show: bool = True) -> None:
	"""Adds an image.uv_min and uv_max represent the normalized texture coordinates of the original image that will be shown.Using(0,0)->(1,1) texture coordinates will generally display the entire texture"""
	...

def add_image_button(name: str = ..., *, value: str = ..., callback: Callable = None, callback_data: Any = None, tint_color: List[float] = (255, 255, 255, 255), background_color: List[float] = (0, 0, 0, 0), parent: str = '', before: str = '', width: int = 0, height: int = 0, frame_padding: int = -1, uv_min: List[float] = (0.0, 0.0), uv_max: List[float] = (1.0, 1.0), show: bool = True, enabled: bool = True) -> None:
	"""Adds an image button.uv_min and uv_max represent the normalized texture coordinates of the original image that will be shown.Using(0,0)->(1,1) texture coordinates will generally display the entire texture"""
	...

def add_image_series(name: str = ..., *, value: str = ..., bounds_min: List[float] = ..., bounds_max: List[float] = ..., uv_min: List[float] = (0.0, 0.0), uv_max: List[float] = (1.0, 1.0), tint_color: List[int] = (255, 255, 255, 255), label: str = '', parent: str = '', before: str = '', show: bool = True, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_indent(name: str = 'indent', *, offset: float = 0.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds an indent to following items. Must be closed with the unindent command."""
	...

def add_input_float(name: str = ..., *, default_value: float = 0.0, min_value: float = 0, max_value: float = 100, min_clamped: bool = False, max_clamped: bool = False, format: str = '%.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, on_enter: bool = False, label: str = '', show: bool = True, step: float = 0.1, step_fast: float = 1.0, readonly: bool = False) -> None:
	"""Adds input for float values."""
	...

def add_input_floatx(name: str = ..., *, default_value: List[float] = (0.0, 0.0, 0.0, 0.0), size: int = 4, min_value: float = 0, max_value: float = 100, min_clamped: bool = False, max_clamped: bool = False, format: str = '%.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, on_enter: bool = False, label: str = '', show: bool = True, readonly: bool = False) -> None:
	"""Adds input for 4 float values."""
	...

def add_input_int(name: str = ..., *, default_value: int = 0, min_value: int = 0, max_value: int = 100, min_clamped: bool = False, max_clamped: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, on_enter: bool = False, label: str = '', show: bool = True, step: int = 1, step_fast: int = 100, readonly: bool = False) -> None:
	"""Adds input for integer values."""
	...

def add_input_intx(name: str = ..., *, default_value: List[int] = (0, 0, 0, 0), size: int = 4, min_value: int = 0, max_value: int = 100, min_clamped: bool = False, max_clamped: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, on_enter: bool = False, label: str = '', show: bool = True, readonly: bool = False) -> None:
	"""Adds input for 4 integer values."""
	...

def add_input_text(name: str = ..., *, default_value: str = '', hint: str = '', multiline: bool = False, no_spaces: bool = False, uppercase: bool = False, tab_input: bool = False, decimal: bool = False, hexadecimal: bool = False, readonly: bool = False, password: bool = False, scientific: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, height: int = 0, on_enter: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds input for text values."""
	...

def add_label_text(name: str = ..., *, default_value: str = '', color: List[float] = (-1, 0, 0, 0), parent: str = '', before: str = '', source: str = '', label: str = '', show: bool = True) -> None:
	"""Adds text with a label. Useful for output values."""
	...

def add_line_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_listbox(name: str = ..., *, items: List[str] = (), default_value: int = 0, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, num_items: int = 3, label: str = '', show: bool = True) -> None:
	"""Adds a listbox."""
	...

def add_logger(name: str = ..., *, log_level: int = 1, auto_scroll: bool = True, auto_scroll_button: bool = True, clear_button: bool = True, copy_button: bool = True, filter: bool = True, width: int = 0, height: int = 0, parent: str = '', before: str = '', show: bool = True, autosize_x: bool = False, autosize_y: bool = False) -> None:
	"""Adds a logging widget."""
	...

def add_menu(name: str = ..., *, label: str = '', show: bool = True, parent: str = '', before: str = '', enabled: bool = True) -> None:
	"""Adds a menu to an existing menu bar. Must be followed by a call to end."""
	...

def add_menu_bar(name: str = ..., *, show: bool = True, parent: str = '', before: str = '') -> None:
	"""Adds a menu bar to a window. Must be followed by a call to end."""
	...

def add_menu_item(name: str = ..., *, default_value: int = False, shortcut: str = '', check: bool = False, callback: Callable = None, callback_data: Any = None, source: str = '', label: str = '', show: bool = True, enabled: bool = True, parent: str = '', before: str = '') -> None:
	"""Adds a menu item to an existing menu."""
	...

def add_metrics_window(name: str = ..., *, width: int = 700, height: int = 500, x_pos: int = 200, y_pos: int = 200, autosize: bool = False, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True) -> None:
	"""Creates a metrics window."""
	...

def add_node(name: str = ..., *, show: bool = True, label: str = '', draggable: bool = True, parent: str = '', before: str = '', x_pos: int = 100, y_pos: int = 100) -> None:
	"""Adds a node to a node editor."""
	...

def add_node_attribute(name: str = ..., *, shape: int = 1, output: bool = False, static: bool = False, show: bool = True, parent: str = '', before: str = '') -> None:
	"""Adds a node attribute."""
	...

def add_node_editor(name: str = ..., *, show: bool = True, parent: str = '', before: str = '', link_callback: Callable = None, delink_callback: Callable = None) -> None:
	"""Adds a node editor."""
	...

def add_node_link(node_editor: str, node_1: str, node_2: str) -> None:
	"""Adds a node link between nodes."""
	...

def add_pie_series(name: str = ..., *, values: List[float] = ..., labels: List[str] = ..., x: float = ..., y: float = ..., radius: float = ..., normalize: bool = False, angle: float = 90.0, format: str = '%0.2f', label: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0) -> None:
	"""Adds a drag point to a plot."""
	...

def add_plot_annotation(name: str = ..., *, default_value: List[float] = (0.0, 0.0), offset: List[float] = (0.0, 0.0), label: str = '', source: str = '', color: List[float] = (0, 0, 0, -1), clamped: bool = True, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_plot_stack(name: str = ..., *, x_axis_name: str = '', y_axis_name: str = '', no_legend: bool = False, no_menus: bool = False, no_box_select: bool = False, no_mouse_pos: bool = False, no_highlight: bool = False, no_child: bool = False, query: bool = False, crosshairs: bool = False, anti_aliased: bool = False, equal_aspects: bool = False, yaxis2: bool = False, yaxis3: bool = False, xaxis_no_gridlines: bool = False, xaxis_no_tick_marks: bool = False, xaxis_no_tick_labels: bool = False, xaxis_log_scale: bool = False, xaxis_time: bool = False, xaxis_invert: bool = False, xaxis_lock_min: bool = False, xaxis_lock_max: bool = False, yaxis_no_gridlines: bool = False, yaxis_no_tick_marks: bool = False, yaxis_no_tick_labels: bool = False, yaxis_log_scale: bool = False, yaxis_invert: bool = False, yaxis_lock_min: bool = False, yaxis_lock_max: bool = False, y2axis_no_gridlines: bool = False, y2axis_no_tick_marks: bool = False, y2axis_no_tick_labels: bool = False, y2axis_log_scale: bool = False, y2axis_invert: bool = False, y2axis_lock_min: bool = False, y2axis_lock_max: bool = False, y3axis_no_gridlines: bool = False, y3axis_no_tick_marks: bool = False, y3axis_no_tick_labels: bool = False, y3axis_log_scale: bool = False, y3axis_invert: bool = False, y3axis_lock_min: bool = False, y3axis_lock_max: bool = False, parent: str = '', before: str = '', width: int = -1, height: int = -1, query_callback: Callable = None, label: str = '', show: bool = True) -> None:
	"""Adds a plot widget."""
	...

def add_popup(name: str = ..., *, mousebutton: int = 1, modal: bool = False, parent: str = '', before: str = '', width: int = 0, height: int = 0, show: bool = True) -> None:
	"""Adds a popup window for an item. This command must come immediately after the item the popup is for. Must be followed by a call to end."""
	...

def add_progress_bar(name: str = ..., *, default_value: float = 0.0, overlay: str = '', parent: str = '', before: str = '', source: str = '', label: str = '', width: int = 0, height: int = 0, show: bool = True) -> None:
	"""Adds a progress bar."""
	...

def add_radio_button(name: str = ..., *, items: List[str] = (), default_value: int = 0, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, horizontal: bool = False, show: bool = True) -> None:
	"""Adds a set of radio buttons. If items is empty, nothing will be shown."""
	...

def add_same_line(name: str = 'sameline', *, xoffset: float = 0.0, spacing: float = -1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Places a widget on the same line as the previous widget. Can also be used for horizontal spacing."""
	...

def add_scatter_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_selectable(name: str = ..., *, default_value: bool = False, callback: Callable = None, callback_data: Any = None, width: int = 0, height: int = 0, parent: str = '', before: str = '', source: str = '', enabled: bool = True, label: str = '', show: bool = True, span_columns: bool = False) -> None:
	"""Adds a selectable."""
	...

def add_separator(name: str = 'separator', *, parent: str = '', before: str = '') -> None:
	"""Adds a horizontal line."""
	...

def add_shade_series(name: str = ..., *, x: List[float] = ..., y1: List[float] = ..., y2: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_simple_plot(name: str = ..., *, value: List[float] = (), overlay: str = '', minscale: float = 0.0, maxscale: float = 0.0, histogram: bool = False, parent: str = '', before: str = '', width: int = 0, height: int = 0, source: str = '', label: str = '', show: bool = True) -> None:
	"""A simple plot for visualization of a set of values"""
	...

def add_slider_float(name: str = ..., *, default_value: float = 0.0, min_value: float = 0.0, max_value: float = 100.0, format: str = '%.3f', vertical: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, height: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds slider for a single float value. CTRL+Click to directly modify the value."""
	...

def add_slider_floatx(name: str = ..., *, default_value: List[float] = (0.0, 0.0, 0.0, 0.0), size: int = 4, min_value: float = 0.0, max_value: float = 100.0, format: str = '%.3f', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds slider for a 4 float values. CTRL+Click to directly modify the value."""
	...

def add_slider_int(name: str = ..., *, default_value: int = 0, min_value: int = 0, max_value: int = 100, format: str = '%d', vertical: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, height: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds slider for a single int value. CTRL+Click to directly modify the value."""
	...

def add_slider_intx(name: str = ..., *, default_value: List[int] = (0, 0, 0, 0), size: int = 4, min_value: int = 0, max_value: int = 100, format: str = '%d', callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', source: str = '', enabled: bool = True, width: int = 0, no_input: bool = False, clamped: bool = False, label: str = '', show: bool = True) -> None:
	"""Adds slider for a 4 int values. CTRL+Click to directly modify the value."""
	...

def add_spacing(name: str = 'spacing', *, count: int = 1, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds vertical spacing."""
	...

def add_stair_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_stem_series(name: str = ..., *, x: List[float] = ..., y: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_style_window(name: str = ..., *, width: int = 700, height: int = 500, x_pos: int = 200, y_pos: int = 200, autosize: bool = False, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True) -> None:
	"""Creates a style window."""
	...

def add_tab(name: str = ..., *, closable: bool = False, label: str = '', show: bool = True, no_reorder: bool = False, leading: bool = False, trailing: bool = False, no_tooltip: bool = False, parent: str = '', before: str = '') -> None:
	"""Adds a tab to a tab bar. Must be closed with the end command."""
	...

def add_tab_bar(name: str = ..., *, reorderable: bool = False, callback: Callable = None, callback_data: Any = None, show: bool = True, parent: str = '', before: str = '') -> None:
	"""Adds a tab bar."""
	...

def add_tab_button(name: str = ..., *, label: str = '', show: bool = True, no_reorder: bool = False, leading: bool = False, trailing: bool = False, no_tooltip: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '') -> None:
	"""Adds a tab button to a tab bar"""
	...

def add_table(name: str = ..., *, header_row: bool = True, width: int = 0, height: int = 0, inner_width: int = 0, show: bool = True, parent: str = '', before: str = '', resizable: bool = False, reorderable: bool = False, hideable: bool = False, sortable: bool = False, context_menu_in_body: bool = False, row_background: bool = False, borders_innerH: bool = False, borders_outerH: bool = False, borders_innerV: bool = False, borders_outerV: bool = False, policy: int = 0, no_host_extendX: bool = False, no_host_extendY: bool = False, no_keep_columns_visible: bool = False, precise_widths: bool = False, no_clip: bool = False, pad_outerX: bool = False, no_pad_outerX: bool = False, no_pad_innerX: bool = False, scrollX: bool = False, scrollY: bool = False) -> None:
	"""Adds managed columns."""
	...

def add_table_column(name: str = ..., *, init_width_or_weight: float = 0.0, show: bool = True, parent: str = '', before: str = '', default_hide: bool = False, default_sort: bool = False, width_stretch: bool = False, width_fixed: bool = False, no_resize: bool = False, no_reorder: bool = False, no_hide: bool = False, no_clip: bool = False, no_sort: bool = False, no_sort_ascending: bool = False, no_sort_descending: bool = False, no_header_width: bool = False, prefer_sort_ascending: bool = False, prefer_sort_descending: bool = False, indent_enable: bool = False, indent_disable: bool = False) -> None:
	"""Changes to next column."""
	...

def add_table_next_column(name: str = 'next_column', *, show: bool = True, parent: str = '', before: str = '') -> None:
	"""Changes to next column."""
	...

def add_text(name: str = ..., *, wrap: int = -1, color: List[float] = (-1, 0, 0, 0), bullet: bool = False, parent: str = '', before: str = '', source: str = '', default_value: str = '', show: bool = True) -> None:
	"""Adds text"""
	...

def add_text_point(name: str = ..., *, x: float = ..., y: float = ..., vertical: bool = False, x_offset: int = 0.0, y_offset: int = 0.0, label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_texture(name: str, data: List[int], width: int, height: int, *, format: int = 0) -> None:
	"""Adds a texture. Incorrect format may yield unexpected results."""
	...

def add_time_picker(name: str = ..., *, default_value: dict = {'hour': 14, 'min': 32, 'sec': 23}, hour24: bool = False, callback: Callable = None, callback_data: Any = None, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Adds a time selector widget."""
	...

def add_tooltip(name: str = ..., *, parent: str = ..., before: str = '', show: bool = True) -> None:
	"""Adds an advanced tool tip for an item. This command must come immediately after the item the tip is for."""
	...

def add_tree_node(name: str = ..., *, label: str = '', show: bool = True, parent: str = '', before: str = '', default_open: bool = False, open_on_double_click: bool = False, open_on_arrow: bool = False, leaf: bool = False, bullet: bool = False) -> None:
	"""Adds a tree node to add items to. Must be closed with the end command."""
	...

def add_vline_series(name: str = ..., *, x: List[float] = ..., label: str = '', source: str = '', parent: str = '', before: str = '', show: bool = True, axis: int = 0, contribute_to_bounds: bool = True) -> None:
	"""Adds a drag point to a plot."""
	...

def add_window(name: str = ..., *, width: int = -1, height: int = -1, x_pos: int = 200, y_pos: int = 200, autosize: bool = False, no_resize: bool = False, no_title_bar: bool = False, no_move: bool = False, no_scrollbar: bool = False, no_collapse: bool = False, horizontal_scrollbar: bool = False, no_focus_on_appearing: bool = False, no_bring_to_front_on_focus: bool = False, menubar: bool = False, no_close: bool = False, no_background: bool = False, label: str = '', show: bool = True, collapsed: bool = False, on_close: Callable = None, min_size: List[int] = [32, 32], max_size: List[int] = [30000, 30000]) -> None:
	"""Creates a new window for following items to be added to."""
	...

def cleanup_dearpygui() -> None:
	"""Cleans up DearPyGui after calling setup_dearpygui."""
	...

def clear_data_grid(data_grid: str) -> None:
	"""Clears data in a data grid"""
	...

def clear_log(*, logger: str = '') -> None:
	"""Clears the logger."""
	...

def clear_selected_links(node_editor: str) -> None:
	"""Clears selected links."""
	...

def clear_selected_nodes(node_editor: str) -> None:
	"""Clears selected nodes."""
	...

def close_popup(item: str) -> None:
	"""Closes a popup."""
	...

def configure_item(item: str, **Kwargs) -> None:
	"""Configures an item"""
	...

def configure_viewport(**Kwargs) -> None:
	"""Shows viewport"""
	...

def create_viewport(*, title: str = ..., width: int = ..., height: int = ..., x_pos: int = ..., y_pos: int = ..., resizable: bool = ..., vsync: bool = ..., always_on_top: bool = ..., maximized_box: bool = ..., minimized_box: bool = ..., border: bool = ..., caption: bool = ..., overlapped: bool = ..., min_width: int = ..., max_width: int = ..., min_height: int = ..., max_height: int = ...) -> None:
	"""Creates a viewport"""
	...

def decrement_texture(name: str) -> None:
	"""Decrements a texture."""
	...

def delete_grid_column(data_grid: str, column: int) -> None:
	"""Delete a column in a data grid."""
	...

def delete_grid_row(data_grid: str, row: int) -> None:
	"""Delete a row in a data grid."""
	...

def delete_item(item: str, *, children_only: bool = False) -> None:
	"""Deletes an item if it exists."""
	...

def delete_node_link(node_editor: str, node_1: str, node_2: str) -> None:
	"""Deletes a node link if it exist."""
	...

def does_item_exist(item: str) -> bool:
	"""Checks if item exists."""
	...

def draw_arrow(name: str = '', *, p1: List[float] = ..., p2: List[float] = ..., color: List[int] = ..., thickness: int = ..., size: int = ..., parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws an arrow on a drawing."""
	...

def draw_bezier_curve(name: str = '', *, p1: List[float] = ..., p2: List[float] = ..., p3: List[float] = ..., p4: List[float] = ..., color: List[int] = ..., thickness: float = 1.0, segments: int = 0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a bezier curve on a drawing."""
	...

def draw_circle(name: str = '', *, center: List[float] = ..., radius: float = ..., color: List[int] = ..., segments: int = 0, thickness: float = 1.0, fill: List[float] = (0, 0, 0, -1), parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a circle on a drawing."""
	...

def draw_image(name: str = '', *, file: str = ..., pmin: List[float] = ..., pmax: List[float] = ..., uv_min: List[float] = (0.0, 0.0), uv_max: List[float] = (1.0, 1.0), color: List[int] = (255, 255, 255, 255), parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws an image on a drawing. p_min (bottom-left) and p_max (upper-right) represent corners of the rectangle the image will be drawn to.Setting the p_min equal to the p_max will sraw the image to with 1:1 scale.uv_min and uv_max represent the normalized texture coordinates of the original image that will be shown. Using (0,0)->(1,1) texturecoordinates will generally display the entire texture."""
	...

def draw_line(name: str = '', *, p1: List[float] = ..., p2: List[float] = ..., color: List[int] = ..., thickness: int = ..., parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a line on a drawing."""
	...

def draw_polygon(name: str = '', *, points: List[List[float]] = ..., color: List[int] = ..., fill: List[float] = (0, 0, 0, -1), thickness: float = 1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a polygon on a drawing."""
	...

def draw_polyline(name: str = '', *, points: List[List[float]] = ..., color: List[int] = ..., closed: bool = False, thickness: float = 1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws lines on a drawing."""
	...

def draw_quad(name: str = '', *, p1: List[float] = ..., p2: List[float] = ..., p3: List[float] = ..., p4: List[float] = ..., color: List[int] = ..., fill: List[float] = (0, 0, 0, -1), thickness: float = 1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a quad on a drawing."""
	...

def draw_rectangle(name: str = '', *, pmin: List[float] = ..., pmax: List[float] = ..., color: List[int] = ..., fill: List[float] = (0, 0, 0, -1), rounding: float = 0.0, thickness: float = 1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a line on a drawing."""
	...

def draw_text(name: str = '', *, pos: List[float] = ..., text: str = ..., color: List[int] = (0, 0, 0, -1), size: int = 10, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws text on a drawing."""
	...

def draw_triangle(name: str = '', *, p1: List[float] = ..., p2: List[float] = ..., p3: List[float] = ..., color: List[int] = ..., fill: List[float] = (0, 0, 0, -1), thickness: float = 1.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Draws a triangle on a drawing."""
	...

def enable_docking(*, shift_only: bool = True, dock_space: bool = False) -> None:
	"""Decrements a texture."""
	...

def end() -> None:
	"""Ends a container."""
	...

def get_active_window() -> str:
	"""Returns the active window name."""
	...

def get_all_items() -> List[str]:
	"""Returns a list of all items."""
	...

def get_dearpygui_version() -> str:
	"""Returns the current version of Dear PyGui."""
	...

def get_delta_time() -> float:
	"""Returns time since last frame."""
	...

def get_drawing_mouse_pos() -> (int, int):
	"""Returns the current mouse position in the currently hovered drawing."""
	...

def get_global_font_scale() -> float:
	"""Returns the global font scale."""
	...

def get_grid_data(data_grid: str) -> List[List[str]]:
	"""Gets data grid data."""
	...

def get_grid_item(data_grid: str, row: int, column: int) -> str:
	"""Gets a data grid's cell value."""
	...

def get_grid_selections(data_grid: str) -> List[List[int]]:
	"""Retrieves data from storage."""
	...

def get_item_callback(item: str) -> Callable:
	"""Returns an item' callback"""
	...

def get_item_callback_data(item: str) -> Any:
	"""Returns an item' callback data"""
	...

def get_item_children[1](item: str) -> List[str]:
	"""Returns a list of an item's children."""
	...

def get_item_configuration(item: str) -> dict:
	"""Returns an items configuration"""
	...

def get_item_parent(item: str) -> str:
	"""Returns an item's parent."""
	...

def get_item_rect_max(item: str) -> [float, float]:
	"""Returns an item's maximum allowable size. [width, height]"""
	...

def get_item_rect_min(item: str) -> [float, float]:
	"""Returns an item's minimum allowable size. [width, height]"""
	...

def get_item_rect_size(item: str) -> [float, float]:
	"""Returns an item's current size. [width, height]"""
	...

def get_item_type(item: str) -> str:
	"""Returns an item's type"""
	...

def get_links(node_editor: str) -> List[List[str]]:
	"""Returns all links. """
	...

def get_log_level(*, logger: str = '') -> int:
	"""Returns the log level."""
	...

def get_mouse_drag_delta() -> (float, float):
	"""Returns the current mouse drag delta in pixels"""
	...

def get_mouse_pos(*, local: bool = True) -> (int, int):
	"""Returns the current mouse position in relation to the active window (minus titlebar) unless local flag is unset."""
	...

def get_plot_mouse_pos() -> (int, int):
	"""Returns the current mouse position in the currently hovered plot."""
	...

def get_plot_query_area(plot: str) -> List[float]:
	"""Returns the bounding axis limits for the query area [x_min, x_max, y_min, y_max]"""
	...

def get_plot_xlimits(plot: str) -> List[float]:
	"""Returns the plots x limits"""
	...

def get_plot_ylimits(plot: str) -> List[float]:
	"""Returns the plots x limits"""
	...

def get_selected_links(node_editor: str) -> List[List[str]]:
	"""Returns selected links."""
	...

def get_selected_nodes(node_editor: str) -> List[str]:
	"""Returns selected nodes."""
	...

def get_total_time() -> float:
	"""Returns total time since app started."""
	...

def get_value(name: str) -> Any:
	"""Returns an item's value or None if there is none."""
	...

def get_windows() -> List[str]:
	"""Returns a list of windows."""
	...

def insert_grid_column(data_grid: str, column_index: int, name: str, column: List[str]) -> None:
	"""Inserts a column into a data grid."""
	...

def insert_grid_row(data_grid: str, row_index: int, row: List[str]) -> None:
	"""Inserts a row into a data grid."""
	...

def is_dearpygui_running() -> bool:
	"""Checks if dearpygui is still running"""
	...

def is_item_activated(item: str) -> bool:
	"""Checks if an item has been activated."""
	...

def is_item_active(item: str) -> bool:
	"""Checks if an item is active."""
	...

def is_item_clicked(item: str) -> bool:
	"""Checks if an item is clicked."""
	...

def is_item_container(item: str) -> bool:
	"""Checks if an item is container."""
	...

def is_item_deactivated(item: str) -> bool:
	"""Checks if an item has been deactivated."""
	...

def is_item_deactivated_after_edit(item: str) -> bool:
	"""Checks if an item has been deactivated after editing."""
	...

def is_item_edited(item: str) -> bool:
	"""Checks if an item has been edited."""
	...

def is_item_focused(item: str) -> bool:
	"""Checks if an item is focused."""
	...

def is_item_hovered(item: str) -> bool:
	"""Checks if an item is hovered."""
	...

def is_item_shown(item: str) -> bool:
	"""Checks if an item is shown."""
	...

def is_item_toggled_open(item: str) -> bool:
	"""Checks if an item is toggled."""
	...

def is_item_visible(item: str) -> bool:
	"""Checks if an item is visible on screen."""
	...

def is_key_down(key: int) -> bool:
	"""Checks if the key is down."""
	...

def is_key_pressed(key: int) -> bool:
	"""Checks if the key is pressed."""
	...

def is_key_released(key: int) -> bool:
	"""Checks if the key is released."""
	...

def is_mouse_button_clicked(button: int) -> bool:
	"""Checks if the mouse button is clicked."""
	...

def is_mouse_button_double_clicked(button: int) -> bool:
	"""Checks if the mouse button is double clicked."""
	...

def is_mouse_button_down(button: int) -> bool:
	"""Checks if the mouse button is pressed."""
	...

def is_mouse_button_dragging(button: int, threshold: float) -> bool:
	"""Checks if the mouse is dragging."""
	...

def is_mouse_button_released(button: int) -> bool:
	"""Checks if the mouse button is released."""
	...

def is_plot_queried(plot: str) -> bool:
	"""Returns true if plot was queried"""
	...

def log(message: Any, *, level: str = 'TRACE', logger: str = '') -> None:
	"""Logs a trace level log."""
	...

def log_debug(message: Any, *, logger: str = '') -> None:
	"""Logs a debug level log."""
	...

def log_error(message: Any, *, logger: str = '') -> None:
	"""Logs a error level log."""
	...

def log_info(message: Any, *, logger: str = '') -> None:
	"""Logs a info level log."""
	...

def log_warning(message: Any, *, logger: str = '') -> None:
	"""Logs a warning level log."""
	...

def maximize_viewport() -> None:
	"""Maximizes viewport"""
	...

def minimize_viewport() -> None:
	"""Minimizes viewport"""
	...

def move_item(item: str, *, parent: str = '', before: str = '') -> None:
	"""Moves an existing item."""
	...

def move_item_down(item: str) -> None:
	"""Moves item down if possible and if it exists."""
	...

def move_item_up(item: str) -> None:
	"""Moves item up if possible and if it exists."""
	...

def open_file_dialog(callback: Callable = None, extensions: str = '') -> None:
	"""Opens an 'open file' dialog."""
	...

def render_dearpygui_frame() -> None:
	"""Renders a DearPyGui frame. Should be called within a user's event loop. Must first call setup_dearpygui outside of event loop."""
	...

def reset_xticks(plot: str) -> None:
	"""Sets plots x ticks and labels back to automatic"""
	...

def reset_yticks(plot: str) -> None:
	"""Sets plots y ticks and labels back to automatic"""
	...

def set_accelerator_callback(callback: Any) -> None:
	"""Callback similar to keypress but used for accelerator keys."""
	...

def set_exit_callback(callback: Any) -> None:
	"""Callback to run when exiting main window."""
	...

def set_font(font: str, size: int, *, item: str = '') -> None:
	"""Adds additional font."""
	...

def set_global_font_scale(scale: float) -> None:
	"""Changes the global font scale."""
	...

def set_grid_data(data_grid: str, data: List[List[str]]) -> None:
	"""Overwrites data grid data."""
	...

def set_grid_headers(data_grid: str, headers: List[str]) -> None:
	"""Sets a data grid's headers."""
	...

def set_grid_item(data_grid: str, row: int, column: int, value: str) -> None:
	"""Sets a data grid's cell value."""
	...

def set_grid_selection(data_grid: str, row: int, column: int, value: bool) -> None:
	"""Sets a data grid's cell selection value."""
	...

def set_item_callback(item: str, callback: Callable, *, callback_data: Any = None) -> None:
	"""Sets an item's callback if applicable."""
	...

def set_item_callback_data(item: str, callback_data: Any) -> None:
	"""Sets an item's callback data if applicable."""
	...

def set_key_down_callback(callback: Callable) -> None:
	"""Sets a callback for a key down event."""
	...

def set_key_press_callback(callback: Callable) -> None:
	"""Sets a callback for a key press event."""
	...

def set_key_release_callback(callback: Callable) -> None:
	"""Sets a callback for a key release event."""
	...

def set_log_level(level: int, *, logger: str = '') -> None:
	"""Sets the log level."""
	...

def set_logger_window_title(title: str) -> None:
	"""Sets the title of the logger window."""
	...

def set_mouse_click_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse click event."""
	...

def set_mouse_double_click_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse double click event."""
	...

def set_mouse_down_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse down event."""
	...

def set_mouse_drag_callback(callback: Callable, threshold: float) -> None:
	"""Sets a callback for a mouse drag event."""
	...

def set_mouse_move_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse move event. Data is the mouse position in local coordinates."""
	...

def set_mouse_release_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse release event."""
	...

def set_mouse_wheel_callback(callback: Callable) -> None:
	"""Sets a callback for a mouse wheel event."""
	...

def set_plot_xlimits(plot: str, xmin: float, xmax: float) -> None:
	"""Sets x axis limits of a plot. (can be undone with set_plot_xlimits_auto()"""
	...

def set_plot_xlimits_auto(plot: str) -> None:
	"""Sets plots x limits to be automatic."""
	...

def set_plot_ylimits(plot: str, ymin: float, ymax: float) -> None:
	"""Sets y axis limits of a plot. (can be undone with set_plot_ylimits_auto()"""
	...

def set_plot_ylimits_auto(plot: str) -> None:
	"""Sets plots y limits to be automatic."""
	...

def set_primary_window(window: str, value: bool) -> None:
	"""Sets the primary window to fill the viewport."""
	...

def set_resize_callback(callback: Callable, *, handler: str = '') -> None:
	"""Sets a callback for a window resize event."""
	...

def set_start_callback(callback: Any) -> None:
	"""Callback to run when starting main window."""
	...

def set_theme_color(constant: int, color: List[float], item: str = '') -> None:
	"""Sets a color of a theme item for when the item is enabled."""
	...

def set_theme_color_disabled(constant: int, color: List[float], item: str = '') -> None:
	"""Sets a color of a theme item for when the item is disabled."""
	...

def set_theme_style(constant: int, style: float, item: str = '') -> None:
	"""Sets a style of a theme item."""
	...

def set_value(name: str, value: Any) -> bool:
	"""Sets an item's value if applicable."""
	...

def set_xticks(plot: str, label_pairs: Any) -> None:
	"""Sets plots x ticks and labels"""
	...

def set_yticks(plot: str, label_pairs: Any) -> None:
	"""Sets plots y ticks and labels"""
	...

def setup_dearpygui() -> None:
	"""Sets up DearPyGui for user controlled rendering. Only call once and you must call cleanup_deapygui when finished."""
	...

def show_logger() -> None:
	"""Shows the logging window. The Default log level is Trace"""
	...

def show_viewport(*, minimized: bool = ..., maximized: bool = ...) -> None:
	"""Shows viewport"""
	...

def stop_dearpygui() -> None:
	"""Stops DearPyGui."""
	...

def unindent(name: str = 'unindent', *, offset: float = 0.0, parent: str = '', before: str = '', show: bool = True) -> None:
	"""Unindents following items."""
	...

