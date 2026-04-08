//给你一个长度为 n 、下标从 0 开始的整数数组 batteryPercentages ，表示 n 个设备的电池百分比。
//
//你的任务是按照顺序测试每个设备 i，执行以下测试操作：
//
//如果 batteryPercentages[i] 大于 0：
//增加 已测试设备的计数。
//将下标 j 在[i + 1, n - 1] 的所有设备的电池百分比减少 1，确保它们的电池百分比 不会低于 0 ，即 batteryPercentages[j] = max(0, batteryPercentages[j] - 1)。
//移动到下一个设备。
//否则，移动到下一个设备而不执行任何测试。
//返回一个整数，表示按顺序执行测试操作后 已测试设备 的数量。
//
//我们可以利用「差分数组」的思想，用 need 表示当前元素需要减 1 的次数，如果当前元素 x = batteryPercentages[i]，当满足 x > need，如果 x > need 时，
//当前元素实际的值为 x−need > 0，i 后面的所有元素都需要减 1，此时需对 need 加 1，当遍历完数组后，返回 need 即可。


int countTestedDevices(int* batteryPercentages, int batteryPercentagesSize) {
    int need = 0;
    for (int i = 0; i < batteryPercentagesSize; i++) {
        if (batteryPercentages[i] > need) {
            need++;
        }
    }
    return need;
}

