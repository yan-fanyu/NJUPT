// pages/home/home.js
// 假设我们使用当前日期所在周作为示例
function getWeekDays() {
  const weekDays = ['一', '二', '三', '四', '五', '六', '日'];
  const dates = [];
  const today = new Date();
  const dayOfWeek = today.getDay();
  const currentDay = today.getDate();
  for (let i = 1; i <= 7; i++) {
    // 计算当前周的每一天
    let diff = i - dayOfWeek;
    let day = new Date(today.getFullYear(), today.getMonth(), currentDay + diff);
    dates.push({
      weekDay: weekDays[i - 1], // 星期几
      date: `${day.getMonth() + 1}月${day.getDate()}日` // 几号
    });
  }
  return dates;
}


Page({

  /**
   * 页面的初始数据
   */
  data: {
    user_id:'',
    selectedDate: '', // 新增一个属性来跟踪选中的日期
    selectedDayHabits:[],
    weekDates: [],
    scrollViewHeight: 0, // 用于存储计算后的scrollView高度
  
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
   this.findUserId();
    this.setData({
      weekDates: getWeekDays()
    });
    this.calculateScrollViewHeight();
  },

  findUserId(){
    wx.cloud.callFunction({
      name:'getOpenId'
    })
    .then(res => {
      console.log('成功',res.result.openid)
      this.setData({
        user_id: res.result.openid
      })
      console.log("this.data.user_id:"+this.data.user_id);
    })
    .catch(res=>{
      console.log('失败',res)
    })
  },


  onPunchCard: function(e) {
    const habId = e.currentTarget.dataset.hab_id;
    const clo_name = e.currentTarget.dataset.clo_name;
    const that = this;
    // 在这里打开一个模态框让用户输入附言
    wx.showModal({
      title: '打卡附言',
      editable: true,
      success: (res) => {
        if (res.confirm && res.content) {
          // 假设 punchCard 是处理打卡操作的云函数
          wx.cloud.callFunction({
            name: 'addpunchCard',
            data: {
              user_id:that.data.user_id,
              clo_name:clo_name,
              selectedDate:that.data.selectedDate,
              comment: res.content
            },
            success: res => {
              
              console.log('打卡成功',res);
              wx.showToast({
                title: '打卡成功',
              });
              that.updateHabitPunchedStatus(habId);
            },
            fail: err => {
              console.error('打卡失败', err);
            }
          });
        }
      }
    });
  },
 // 更新习惯的打卡状态
 updateHabitPunchedStatus: function(habId) {
  const selectedDayHabits = this.data.selectedDayHabits.map(habit => {
    if (habit.clo_id === habId) { // 确保这里的属性名与数据模型匹配
      return { ...habit, punched: true }; // 标记为已打卡
    }
    return habit;
  });
  this.setData({ 
    selectedDayHabits:selectedDayHabits // 更新已打卡的习惯状态
  });
},


  onDayClick: function(e) {
    const that = this;
    const selectedDate = e.currentTarget.dataset.date;
    this.setData({ 
      selectedDate :selectedDate
    }); // 更新选中的日期
    // 假设 getHabitsByDate 是调用云函数获取习惯的函数
    console.log(selectedDate);
   const user_id = this.data.user_id;
    wx.cloud.callFunction({
      name: 'getClocksByDate',
      data: { 
        user_id: user_id,
        clo_date: selectedDate,
      },
      success: res => {
        const habits = res.result.data.map(item => ({ 
          clo_id: item._id, // 假设每个习惯对象有一个唯一的_id字段
          clo_name: item.clo_name,
          punched: false // 默认设置为未打卡
        }));
        that.setData({
          selectedDayHabits: habits
        });
        
      },
      fail: err => {
        console.error('获取习惯失败', err);
      }
    });
  },


  calculateScrollViewHeight() {
    const that = this;
    wx.getSystemInfo({
      success: function (res) {
        let tabBarHeight = 10; // tabBar的高度，根据你的实际情况设置
        let calendarHeight = 13; // 日历视图的高度，根据你的实际情况设置
        let statusBarHeight = res.statusBarHeight; // 状态栏的高度
        let navigationBarHeight = 0; // 导航栏的高度，大概值，可能需要根据实际进行调整

        // 计算scrollView的高度：屏幕高度减去tabBar、日历、状态栏和导航栏的高度
        let scrollViewHeight = res.windowHeight - tabBarHeight - calendarHeight - statusBarHeight - navigationBarHeight;
        
        that.setData({
          scrollViewHeight: scrollViewHeight,
        });
        console.log("高度是："+scrollViewHeight)
      }
    });
  },

  onAddIconClick: function() {
    wx.navigateTo({
      url: `/pages/add/add?user_id=${this.data.user_id}&selectedDate=${encodeURIComponent(this.data.selectedDate)}` // 假设你要跳转的新页面的路径是 `/pages/new-page/new-page`
    });
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  }
})