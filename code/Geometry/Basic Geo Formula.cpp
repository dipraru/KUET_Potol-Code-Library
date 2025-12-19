circumradius = (a * b * c) / (4 * area); //pori
inradius = area / s; //onto
isosceles_side = (b / 4) * sqrt(4 * a * a - b * b); // a same
equilateral_area = (sqrt(3) / 4) * a * a;
regular_polygon_area = (n * a * a / 4) * (1 / tan(M_PI / n));
point_line_distance = abs(a*x + b*y + c) / sqrt(a*a + b*b);
two_point_distance = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
area_triangle_sine = 0.5 * a * b * sin(C);
line_intercept = y1 - (perpendicular_slope * x1);
perpendicular_slope = -1 / line_slope;
sine_rule = a / sin(A) == b / sin(B) == c / sin(C) == 2 * circumradius;
cosine_rule = c * c = a * a + b * b - 2 * a * b * cos(C);
herons_area = sqrt(s * (s - a) * (s - b) * (s - c)); // s = (a+b+c)/2
centroid = ( (x1 + x2 + x3) / 3 , (y1 + y2 + y3) / 3 )
orthocenter = (tanA*x1 + tanB*x2 + tanC*x3) / (tanA + tanB + tanC) , (tanA*y1 + tanB*y2 + tanC*y3) / (tanA + tanB + tanC) )  
incenter = ( (a*x1 + b*x2 + c*x3) / (a + b + c) , (a*y1 + b*y2 + c*y3) / (a + b + c) )
circumcenter = intersection of perpendicular bisectors of any two sides
median = ( (x1 + x2) / 2 , (y1 + y2) / 2 )