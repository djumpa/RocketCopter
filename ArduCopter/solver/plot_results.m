function[] = plot_results(tv, r, v, u, m ,g , T_max)

u_norms = norms(u);
u_dirs = 90 - rad2deg(atan2(u(2,:), u(1,:)));
T_vals = u_norms .* m;

figure; hold on;
plot(tv, r(1,:), tv, r(2,:));
title('Position (m)');

figure; hold on;
plot(tv, v(1,:), tv, v(2,:));
title('Velocity (m/s)');

figure; hold on;
plot(r(1,:), r(2,:));
quiver(r(1,:), r(2,:), u(1,:), u(2,:), .25);
title('Trajectory (m)');

figure;
plot(tv, u(1,:), tv, u(2,:));
title('Acceleration (m/s^2)');

figure; hold on;
plot(tv, T_vals);
title('Thrust (N)');

figure; hold on;
plot(tv, T_vals./(T_max));
title('Thrust (%)');

figure; hold on;
plot(tv, u_norms./abs(g));
title('TWR');

figure;
plot(tv, u_norms);
title('Acceleration (m/s^2)');

figure;
plot(tv, u_dirs);
title('Acceleration (deg)');

figure;
plot(tv, m);
title('Mass (kg)');







