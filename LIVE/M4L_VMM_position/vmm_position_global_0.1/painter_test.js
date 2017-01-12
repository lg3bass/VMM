function paint()
{

	var viewsize = mgraphics.size;

	var valrange = box.getattr("size");

	var width = viewsize[0];

	var height = viewsize[1];

var border = 1;
var bordercolor = [ 0.375, 0.375, 0.375,1 ];

var rounded = 6;
if (box.getattr("rounded")) rounded = box.getattr("rounded");

// call original object paint method
mgraphics.parentpaint();

mgraphics.set_source_rgba(bordercolor);
mgraphics.rectangle_rounded(border/2, border/2, width-border, height-border, rounded, rounded);
mgraphics.set_line_width(border);
mgraphics.stroke();
}