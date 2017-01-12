{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 1,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 104.0, 104.0, 900.0, 688.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 10.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 12.0,
					"id" : "obj-116",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 430.0, 456.0, 184.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 1.0, 194.0, 20.0 ],
					"style" : "",
					"text" : "VMM GLOBAL POSITION v0.1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-104",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2.0, 96.0, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 100.0, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Trans Z",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-105",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 668.0, 96.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 100.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[10]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[10]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-106",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 596.0, 96.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 100.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[11]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu[11]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-107",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 94.0, 96.0, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 100.0, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text[5]",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text[5]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-108",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 558.0, 96.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 100.0, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[20]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[20]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-109",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 456.0, 96.0, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 100.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-110",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 228.0, 96.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 100.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[21]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[21]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-111",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 126.0, 96.0, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 100.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-112",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 414.0, 96.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 100.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[22]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[22]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-113",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 372.0, 96.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 100.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[23]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[23]"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-114",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 270.0, 96.0, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 100.0, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab[5]",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab[5]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-93",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 2.0, 80.0, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 84.0, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Trans Y",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-94",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 668.0, 81.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 84.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[8]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[8]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-95",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 596.0, 81.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 84.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[9]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu[9]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-96",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 94.0, 81.5, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 84.0, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text[4]",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-97",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 558.0, 81.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 84.0, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[16]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[16]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-98",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 456.0, 81.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 84.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-99",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 228.0, 81.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 84.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[17]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[17]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-100",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 126.0, 81.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 84.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-101",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 414.0, 81.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 84.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[18]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[18]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-102",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 372.0, 81.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 84.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[19]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[19]"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-103",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 270.0, 81.5, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 84.0, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab[4]",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 0.0, 63.0, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 66.0, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Trans X",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-83",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 666.0, 64.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 67.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[6]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[6]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-84",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 594.0, 64.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 67.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[7]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu[7]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-85",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 92.0, 64.5, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 67.5, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text[3]",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-86",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 556.0, 64.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 67.5, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[12]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[12]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-87",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 454.0, 64.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 67.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-88",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 226.0, 64.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 67.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[13]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[13]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-89",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 124.0, 64.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 67.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-90",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 412.0, 64.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 67.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[14]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[14]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-91",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 370.0, 64.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 67.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[15]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[15]"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-92",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 268.0, 64.5, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 67.5, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab[3]",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-71",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 0.0, 49.0, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 50.0, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Rotate Z",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-72",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 666.0, 50.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 51.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[4]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-73",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 594.0, 50.5, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 51.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[5]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu[5]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-74",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 92.0, 50.5, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 51.5, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text[2]",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-75",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 556.0, 50.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 51.5, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[8]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[8]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-76",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 454.0, 50.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 51.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 226.0, 50.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 51.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[9]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[9]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-78",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 124.0, 50.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 51.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-79",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 412.0, 50.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 51.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[10]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[10]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-80",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 370.0, 50.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 51.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[11]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[11]"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-81",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 268.0, 50.5, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 51.5, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab[2]",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ -2.0, 32.5, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 34.0, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Rotate Y",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 664.0, 34.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 35.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[2]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 592.0, 34.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 35.5, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[3]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-62",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 90.0, 34.0, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 35.5, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text[1]",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-64",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 554.0, 34.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 35.5, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[4]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[4]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 452.0, 34.0, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 35.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-66",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 224.0, 34.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 35.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[5]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[5]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-67",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 122.0, 34.0, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 35.5, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-68",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 410.0, 34.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 35.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[6]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[6]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-69",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 368.0, 34.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 35.5, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[7]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[7]"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-70",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 266.0, 34.0, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 35.5, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab[1]",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-57",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 389.0, 157.0, 150.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 0.0, 18.5, 90.0, 18.0 ],
					"style" : "",
					"text" : "Global Rotate X",
					"textjustification" : 2
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-55",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 577.0, 17.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 4.0, 70.0, 15.0 ],
					"style" : "",
					"text" : "tween curve",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-54",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 506.0, 17.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 4.0, 70.0, 15.0 ],
					"style" : "",
					"text" : "tween type",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-48",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 468.0, 14.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 4.0, 36.0, 15.0 ],
					"style" : "",
					"text" : "ms",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-43",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 363.0, 15.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 4.0, 82.0, 15.0 ],
					"style" : "",
					"text" : "tween duration"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-42",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 281.0, 17.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 4.0, 82.0, 15.0 ],
					"style" : "",
					"text" : "range [ low | high ]"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-40",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 176.0, 15.0, 176.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 4.0, 100.0, 15.0 ],
					"style" : "",
					"text" : "key random | key tween"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 8.0,
					"id" : "obj-32",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 77.0, 23.0, 129.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 4.0, 40.0, 15.0 ],
					"style" : "",
					"text" : "value",
					"textjustification" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-53",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 486.0, 353.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 668.0, 20.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu[1]",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "bounce", "circ", "cubic", "expo", "linear", "quad", "quart", "quint", "sine" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 4.0 ]
						}

					}
,
					"varname" : "live.menu[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-50",
					"maxclass" : "live.menu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 471.0, 338.0, 100.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 596.0, 20.0, 70.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.menu",
							"parameter_shortname" : "live.menu",
							"parameter_type" : 2,
							"parameter_enum" : [ "easeIn", "easeOut", "easeInOut" ],
							"parameter_initial_enable" : 1,
							"parameter_initial" : [ 2 ]
						}

					}
,
					"varname" : "live.menu"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-49",
					"maxclass" : "live.text",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 450.0, 344.0, 40.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 92.0, 20.0, 30.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.text",
							"parameter_shortname" : "live.text",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "val1", "val2" ]
						}

					}
,
					"text" : "edit",
					"texton" : "edit",
					"varname" : "live.text"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-47",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 657.0, 180.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 558.0, 20.0, 36.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[3]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_mmax" : 5000.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[3]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 555.0, 176.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 456.0, 20.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 555.0, 178.0, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 226.0, 20.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[2]",
							"parameter_shortname" : "live.numbox[2]",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"orientation" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 394.0, 343.5, 20.0, 140.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 20.0, 100.0, 15.0 ],
					"style" : "",
					"thickness" : 75.0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 485.0, 297.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 310.0, 20.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox[1]",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "live.numbox",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 394.0, 343.5, 36.0, 15.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 268.0, 20.0, 40.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.numbox",
							"parameter_shortname" : "live.numbox",
							"parameter_type" : 0,
							"parameter_mmin" : -360.0,
							"parameter_mmax" : 360.0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.numbox"
				}

			}
, 			{
				"box" : 				{
					"button" : 1,
					"id" : "obj-27",
					"maxclass" : "live.tab",
					"num_lines_patching" : 1,
					"num_lines_presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 585.5, 343.5, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 20.0, 100.0, 15.0 ],
					"rounded" : 10.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.tab",
							"parameter_shortname" : "live.tab",
							"parameter_type" : 2,
							"parameter_enum" : [ "random", "tween" ],
							"parameter_unitstyle" : 0
						}

					}
,
					"spacing_x" : 3.0,
					"spacing_y" : 3.0,
					"varname" : "live.tab"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-39",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 52.0, 164.0, 58.0, 20.0 ],
					"style" : "",
					"text" : "route 0 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 161.0, 204.5, 93.0, 20.0 ],
					"style" : "",
					"text" : "bgcolor 1 1 0 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 204.5, 107.0, 20.0 ],
					"style" : "",
					"text" : "bgcolor 1 1 0 0.05"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 52.0, 43.0, 29.5, 20.0 ],
					"style" : "",
					"text" : "!- 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 281.0, 57.5, 34.0, 20.0 ],
					"style" : "",
					"text" : "gate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 114.5, 79.5, 108.0, 20.0 ],
					"style" : "",
					"text" : "s ---GRXautomate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "live.toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 264.5, 14.5, 22.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.0, 308.5, 15.0, 15.0 ],
					"rounded" : 15.0,
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "switch_global_rotate_X",
							"parameter_shortname" : "switch_global_rotate_X",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "off", "on" ],
							"parameter_invisible" : 1
						}

					}
,
					"varname" : "switch_global_rotate_X"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 136.5, 14.5, 150.0, 18.0 ],
					"style" : "",
					"text" : "GLOBAL ROTATE X"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 465.0, 616.0, 56.0, 20.0 ],
					"style" : "",
					"text" : "r ---track"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 465.0, 642.0, 163.0, 20.0 ],
					"style" : "",
					"text" : "sprintf set /setGlobalRotX %i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 565.0, 667.5, 55.0, 20.0 ],
					"style" : "",
					"text" : "prepend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 565.0, 696.0, 37.0, 20.0 ],
					"style" : "",
					"text" : "s out"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 54.0, 616.0, 56.0, 20.0 ],
					"style" : "",
					"text" : "r ---track"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 54.0, 642.0, 179.0, 20.0 ],
					"style" : "",
					"text" : "sprintf set /tweenGlobalRotX %i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 154.0, 667.5, 55.0, 20.0 ],
					"style" : "",
					"text" : "prepend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 154.0, 696.0, 37.0, 20.0 ],
					"style" : "",
					"text" : "s out"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 267.0, 616.0, 56.0, 20.0 ],
					"style" : "",
					"text" : "r ---track"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 267.0, 642.0, 171.0, 20.0 ],
					"style" : "",
					"text" : "sprintf set /randGlobalRotX %i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 367.0, 667.5, 55.0, 20.0 ],
					"style" : "",
					"text" : "prepend"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 367.0, 696.0, 37.0, 20.0 ],
					"style" : "",
					"text" : "s out"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 465.0, 383.0, 91.0, 20.0 ],
					"style" : "",
					"text" : "r ---G_Rot_edit"
				}

			}
, 			{
				"box" : 				{
					"comment" : "",
					"id" : "obj-2",
					"maxclass" : "inlet",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 296.0, 9.5, 30.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"int" : 1,
					"maxclass" : "gswitch2",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 301.0, 512.0, 39.0, 32.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 340.0, 142.0, 59.0, 20.0 ],
					"style" : "",
					"text" : "active $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 359.0, 322.0, 73.0, 20.0 ],
					"style" : "",
					"text" : "outputvalue"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 442.0, 322.0, 59.0, 20.0 ],
					"style" : "",
					"text" : "active $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 307.0, 322.0, 43.0, 20.0 ],
					"style" : "",
					"text" : "set $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "gswitch2",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 252.0, 559.0, 68.0, 32.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 276.0, 435.0, 20.0, 20.0 ],
					"style" : "",
					"text" : "t i"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-63",
					"maxclass" : "live.toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 301.0, 435.0, 22.0, 24.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.0, 291.5, 15.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_enabled",
							"parameter_shortname" : "GRX_set",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "off", "on" ],
							"parameter_invisible" : 1
						}

					}
,
					"varname" : "globRotX_enabled"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"maxclass" : "live.toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 252.0, 99.5, 20.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.0, 274.5, 15.0, 15.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_randSwitch",
							"parameter_shortname" : "GRX_rand",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "off", "on" ],
							"parameter_invisible" : 1
						}

					}
,
					"varname" : "globRotX_randSwitch"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 329.0, 375.0, 81.0, 20.0 ],
					"restore" : [ 0.0 ],
					"saved_object_attributes" : 					{
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "pattr G_RotX",
					"varname" : "G_RotX"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "gswitch2",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 276.0, 238.0, 39.0, 32.0 ],
					"style" : "",
					"varname" : "gswitch2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-51",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 276.0, 375.0, 44.0, 47.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 213.0, 274.0, 44.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_value",
							"parameter_shortname" : "GRotX",
							"parameter_type" : 0,
							"parameter_mmin" : -180.0,
							"parameter_mmax" : 180.0,
							"parameter_unitstyle" : 0,
							"parameter_mapping_index" : 9
						}

					}
,
					"varname" : "globRotX_value"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 307.0, 288.0, 125.0, 22.0 ],
					"style" : "",
					"text" : "expr random($i2\\, $i3)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "live.button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 296.0, 99.5, 30.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 95.0, 282.5, 30.0, 30.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_trigger",
							"parameter_shortname" : "LRX_FIRE",
							"parameter_type" : 2,
							"parameter_mmax" : 1.0,
							"parameter_enum" : [ "off", "on" ]
						}

					}
,
					"varname" : "globRotX_trigger"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 413.0, 235.0, 44.0, 47.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 169.0, 274.0, 44.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_max",
							"parameter_shortname" : "GRXmax",
							"parameter_type" : 0,
							"parameter_mmin" : -180.0,
							"parameter_mmax" : 180.0,
							"parameter_unitstyle" : 0,
							"parameter_invisible" : 1
						}

					}
,
					"varname" : "globRotX_max"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 413.0, 177.0, 44.0, 47.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 125.0, 274.0, 44.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "globRotX_min",
							"parameter_shortname" : "GRXmin",
							"parameter_type" : 0,
							"parameter_mmin" : -180.0,
							"parameter_mmax" : 180.0,
							"parameter_unitstyle" : 0,
							"parameter_invisible" : 1
						}

					}
,
					"varname" : "globRotX_min"
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"background" : 1,
					"bgcolor" : [ 1, 1, 0, 0.0 ],
					"id" : "obj-24",
					"maxclass" : "panel",
					"mode" : 0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 52.0, 246.0, 202.0, 59.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 75.0, 272.0, 200.0, 65.0 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-19", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-23", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-52", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-7", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-51" : [ "globRotX_value", "GRotX", 0 ],
			"obj-85" : [ "live.text[3]", "live.text", 0 ],
			"obj-33" : [ "globRotX_trigger", "LRX_FIRE", 0 ],
			"obj-77" : [ "live.numbox[9]", "live.numbox[2]", 0 ],
			"obj-31" : [ "globRotX_max", "GRXmax", 0 ],
			"obj-81" : [ "live.tab[2]", "live.tab", 0 ],
			"obj-30" : [ "globRotX_min", "GRXmin", 0 ],
			"obj-53" : [ "live.menu[1]", "live.menu", 0 ],
			"obj-64" : [ "live.numbox[4]", "live.numbox[2]", 0 ],
			"obj-108" : [ "live.numbox[20]", "live.numbox[2]", 0 ],
			"obj-94" : [ "live.menu[8]", "live.menu", 0 ],
			"obj-68" : [ "live.numbox[6]", "live.numbox", 0 ],
			"obj-66" : [ "live.numbox[5]", "live.numbox[2]", 0 ],
			"obj-60" : [ "globRotX_randSwitch", "GRX_rand", 0 ],
			"obj-50" : [ "live.menu", "live.menu", 0 ],
			"obj-83" : [ "live.menu[6]", "live.menu", 0 ],
			"obj-91" : [ "live.numbox[15]", "live.numbox", 0 ],
			"obj-49" : [ "live.text", "live.text", 0 ],
			"obj-88" : [ "live.numbox[13]", "live.numbox[2]", 0 ],
			"obj-95" : [ "live.menu[9]", "live.menu", 0 ],
			"obj-74" : [ "live.text[2]", "live.text", 0 ],
			"obj-110" : [ "live.numbox[21]", "live.numbox[2]", 0 ],
			"obj-75" : [ "live.numbox[8]", "live.numbox[2]", 0 ],
			"obj-37" : [ "live.numbox[1]", "live.numbox", 0 ],
			"obj-72" : [ "live.menu[4]", "live.menu", 0 ],
			"obj-47" : [ "live.numbox[3]", "live.numbox[2]", 0 ],
			"obj-70" : [ "live.tab[1]", "live.tab", 0 ],
			"obj-97" : [ "live.numbox[16]", "live.numbox[2]", 0 ],
			"obj-73" : [ "live.menu[5]", "live.menu", 0 ],
			"obj-79" : [ "live.numbox[10]", "live.numbox", 0 ],
			"obj-59" : [ "live.menu[2]", "live.menu", 0 ],
			"obj-45" : [ "live.numbox[2]", "live.numbox[2]", 0 ],
			"obj-62" : [ "live.text[1]", "live.text", 0 ],
			"obj-36" : [ "live.numbox", "live.numbox", 0 ],
			"obj-112" : [ "live.numbox[22]", "live.numbox", 0 ],
			"obj-80" : [ "live.numbox[11]", "live.numbox", 0 ],
			"obj-101" : [ "live.numbox[18]", "live.numbox", 0 ],
			"obj-114" : [ "live.tab[5]", "live.tab", 0 ],
			"obj-61" : [ "live.menu[3]", "live.menu", 0 ],
			"obj-63" : [ "globRotX_enabled", "GRX_set", 0 ],
			"obj-99" : [ "live.numbox[17]", "live.numbox[2]", 0 ],
			"obj-96" : [ "live.text[4]", "live.text", 0 ],
			"obj-106" : [ "live.menu[11]", "live.menu", 0 ],
			"obj-107" : [ "live.text[5]", "live.text", 0 ],
			"obj-113" : [ "live.numbox[23]", "live.numbox", 0 ],
			"obj-86" : [ "live.numbox[12]", "live.numbox[2]", 0 ],
			"obj-92" : [ "live.tab[3]", "live.tab", 0 ],
			"obj-105" : [ "live.menu[10]", "live.menu", 0 ],
			"obj-3" : [ "switch_global_rotate_X", "switch_global_rotate_X", 0 ],
			"obj-69" : [ "live.numbox[7]", "live.numbox", 0 ],
			"obj-102" : [ "live.numbox[19]", "live.numbox", 0 ],
			"obj-84" : [ "live.menu[7]", "live.menu", 0 ],
			"obj-90" : [ "live.numbox[14]", "live.numbox", 0 ],
			"obj-27" : [ "live.tab", "live.tab", 0 ],
			"obj-103" : [ "live.tab[4]", "live.tab", 0 ]
		}
,
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
