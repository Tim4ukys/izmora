db = { }

db_info = {
	name = "Скорость воздуха",
	type = "hist", -- line, hist
	axis = { "", "" }
}

--[[
a = 30

k = (math.pi/2) / a
for i = 0, a*4 do 
	t = k*i
	db[i] = { 
		x = t,  
		y = math.sin(t),
		err_x = 0.025,
		err_y = 0.01
	}
end
]]

db = { 
	1.7, 1.3, 1.5, 1.3, 1.5, 2.1, 1.5, 1.0, 1.8, 1.5
}
