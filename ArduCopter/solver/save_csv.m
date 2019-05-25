%save results to csv
control_rate = 400; % Hz
control_time = 0:1/control_rate:G.tv(end);

thrust = norms(G.u).*G.m./G.T_max;
thrust_interp = interp1(G.tv,thrust,control_time);

angle = 90 - rad2deg(atan2(G.u(2,:), G.u(1,:)));
angle_interp = interp1(G.tv,angle,control_time);

csvwrite('hoverslam.csv',[thrust_interp;angle_interp]')