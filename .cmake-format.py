# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: CC0-1.0

# ----------------------------------
# Options affecting listfile parsing
# ----------------------------------
with section("parse"):

	# Specify structure for custom cmake functions
	additional_commands = {
		'set_target_properties': {
			'kwargs': {
				'PROPERTIES': {
					'kwargs': {
						'MACOSX_BUNDLE_GUI_IDENTIFIER': 1,
						'MACOSX_BUNDLE_BUNDLE_VERSION': 1,
						'MACOSX_BUNDLE_SHORT_VERSION_STRING': 1
					}
				}
			}
		},
		'qt_generate_qml_plugin_import': {
			'kwargs': {
				'EXTRA_PLUGIN': '+',
				'OUTPUT': 1,
				'OUTPUT_DIR': 1,
				'QML_DIR': 1,
				'QML_SRC': 1
			},
			'pargs': {
				'flags': ['VERBOSE'],
				'nargs': '1+'
			}
		}
	}

# -----------------------------
# Options affecting formatting.
# -----------------------------
with section("format"):

	# How many spaces to tab for indent
	tab_size = 4

	# If true, lines are indented using tab characters (utf-8 0x09) instead of
	# <tab_size> space characters (utf-8 0x20). In cases where the layout would
	# require a fractional tab character, the behavior of the  fractional
	# indentation is governed by <fractional_tab_policy>
	use_tabchars = True

	# If <use_tabchars> is True, then the value of this variable indicates how
	# fractional indentions are handled during whitespace replacement. If set to
	# 'use-space', fractional indentation is left as spaces (utf-8 0x20). If set
	# to `round-up` fractional indentation is replaced with a single tab character
	# (utf-8 0x09) effectively shifting the column to the next tabstop
	fractional_tab_policy = 'round-up'

	# If a statement is wrapped to more than one line, than dangle the closing
	# parenthesis on its own line.
	dangle_parens = True

# ------------------------------------------------
# Options affecting comment reflow and formatting.
# ------------------------------------------------
with section("markup"):

	# If comment markup is enabled, don't reflow the first comment block in each
	# listfile. Use this to preserve formatting of your copyright/license
	# statements.
	first_comment_is_literal = True
