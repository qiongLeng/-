Page({
    data: {
        Temp: 0,
        Hum: 0,
        Alarm: false,
        LED: false
    },
    config: {
        authorization: "version=2018-10-31&res=products%2FxX6gucP6ZM%2Fdevices%2FTest1&et=1842701951&method=md5&sign=IfgpYCYWAljm3CUljuPSZw%3D%3D",
        product_id: "xX6gucP6ZM",
        device_name: "Test1",
        getinfo_url: 'https://iot-api.heclouds.com/thingmodel/query-device-property?product_id=xX6gucP6ZM&device_name=Test1',
        setinfo_url: 'https://iot-api.heclouds.com/thingmodel/set-device-property'
    },

    Onenet_GetInfo() {
        wx.request({
            url: this.config.getinfo_url,
            header: {
                'authorization': this.config.authorization
            },
            method: "GET",
            success: (e) => {
                if (e.data.code === 0) {
                    let newData = {};
                    e.data.data.forEach(item => {
                        if (item.identifier === 'temp') newData.Temp = item.value;
                        if (item.identifier === 'humidity') newData.Hum = item.value;
                        if (item.identifier === 'Alarm') newData.Alarm = (item.value === 'true' || item.value === true);
                        if (item.identifier === 'LED') newData.LED = (item.value === 'true' || item.value === true);
                    });
                    this.setData(newData);
                }
            }
        })
    },

    Onenet_SetAlarmInfo(event) {
        const is_checked = event.detail.value;
        wx.showToast({ title: '操作成功', icon: 'success', duration: 1000 });
        wx.request({
            url: this.config.setinfo_url,
            header: { 'authorization': this.config.authorization },
            method: "POST",
            data: {
                "product_id": this.config.product_id,
                "device_name": this.config.device_name,
                "params": {
                    "Alarm": is_checked ? true : false
                }
            },
            success: (e) => {
                if (e.data.code === 0) {
                    this.setData({ Alarm: is_checked });
                }
            }
        })
    },

    Onenet_SetLedInfo(event) {
        const is_checked = event.detail.value;
        wx.showToast({ title: '操作成功', icon: 'success', duration: 1000 });
        wx.request({
            url: this.config.setinfo_url,
            header: { 'authorization': this.config.authorization },
            method: "POST",
            data: {
                "product_id": this.config.product_id,
                "device_name": this.config.device_name,
                "params": {
                    "LED": is_checked ? true : false
                }
            },
            success: (e) => {
                if (e.data.code === 0) {
                    this.setData({ LED: is_checked });
                }
            }
        })
    },

    onLoad() {
        this.Onenet_GetInfo();
        setInterval(() => this.Onenet_GetInfo(), 5000);
    }
})