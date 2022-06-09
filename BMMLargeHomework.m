clear;
dataPosStr = 'E:\ProjectsVisualStudio\Mutation\result\'; % 填写数据所在目录 
dataStr = [dataPosStr, '*.txt']; % 填写数据名称格式
D = dir(dataStr);
lastHamming = zeros(1, length(D));
param = strings(1, length(D));
for i = 1:length(D)
    param(1, i) = D(i).name;
    x = load([dataPosStr D(i).name]);
    lastHamming(1, i) = mean(x(101:1001, 2));
end
temp = zeros(1, 36);
for i = 397:432
    temp(1, i - 396) = lastHamming(1, i);
end
for i = 433:length(D)
    lastHamming(1, i - 36) = lastHamming(1, i); 
end
for i = 1:36
    lastHamming(1, length(D) - 36 + i) = lastHamming(1, i);
end
for i = 1:36
    lastHamming(1, i) = temp(1, i);
end
plot(1:length(D), lastHamming);