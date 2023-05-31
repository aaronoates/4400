
ylim([0 40000]);
xlim([0 3000]);
time_to_42 = [1000, 3400];
working_size = [2000, 3000];
time_to_largest = [11800, 37000];
plot(working_size, time_to_largest)
hold on
plot(working_size, time_to_42)
hold off
xlabel('working size')
ylabel('time')
legend('time to find largest value','time to find value 42')



