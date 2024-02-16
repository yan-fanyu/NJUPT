// pages/add/add.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    user_id:"",
    selectedDate:"",
    habitList:[],
    selectedSlot: '', // 用户选择的习惯名称
    modalVisible: false, // 控制模态弹窗是否显示
    startDate: '', // 开始时间
    endDate: '', // 截止时间
    deadline: '' // 每天截止日期
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    this.setData({
      user_id: options.user_id,
      selectedDate: decodeURIComponent(options.selectedDate)
    })
    console.log("add页面加载时："+options.user_id);
    this.fetchHabits(); // 调用获取习惯列表的函数
  },

    // 获取用户习惯的函数
    fetchHabits() {
      const user_id = this.data.user_id;
      const that = this;
      wx.cloud.callFunction({
        name: 'queryHabitsByUserId',
        data: {
          user_id:user_id
        }, // 如果需要的话，这里可以传递参数
        success: res => {
            that.setData({
              habitList: res.result.data
            });
        },
        fail: err => {
          console.error('云函数调用失败：', err);
        }
      });
    },

     // picker选择器变化时的事件处理函数
  bindPickerChange: function(e) {
    const index = e.detail.value; // picker返回的是选中项的索引
    const selectedHabit = this.data.habitList[index]; // 获取选中的习惯
    const that = this;
    if (selectedHabit) {
      that.setData({
        selectedSlot: selectedHabit.hab_name // 设置选中的习惯名称
      });
    }
  },

  showModal() {
    this.setData({
      modalVisible: true
    });
  },
  hideModal() {
    this.setData({
      modalVisible: false
    });
    console.log("hidemodel");
  },
  formSubmit(e) {
    const that = this;
    const user_id = this.data.user_id;
    // 处理表单数据
    console.log('formsubmit:',e.detail.value);
    
    wx.cloud.callFunction({
      name: 'addHabit',
      data: {
        hab_name: e.detail.value.hab_name,
        user_id: user_id // 通常这会是一个从小程序获取的用户唯一标识
      },
      success: function(res) {
        console.log('添加成功', res)
        that.updateHabitId(e.detail.value.hab_name,user_id);
      },
      fail: function(err) {
        console.error('添加失败', err)
      }
    });
    // 关闭模态弹窗
    this.hideModal();
  },

  updateHabitId(habit_name,user_id){
    wx.cloud.callFunction({
      name: 'updateHabitId',
      data: {
        user_id: user_id, // 用户的 ID
        hab_name: habit_name, // 习惯的名称
      },
      success: function(res) {
        if (res.result.code === 404) {
          console.log('没有找到记录');
        } else {
          console.log('更新成功', res);
        }
      },
      fail: function(err) {
        console.error('更新失败', err);
      }
    });
    
  },

  onStartDateChange: function(e) {
    this.setData({
      startDate: e.detail.value // 设置开始时间为选中的日期
    });
  },
  onEndDateChange: function(e) {
    this.setData({
      endDate: e.detail.value // 设置截止时间为选中的日期
    });
  },


  onDeadlineChange: function(e) {
    this.setData({
      deadline: e.detail.value // 更新截止日期
    });
  },


  confirmAction: function() {
    // 这里可以添加点击确定按钮需要执行的代码
    const user_id = this.data.user_id;
    const selectedSlot = this.data.selectedSlot;
    const startDate=this.data.startDate;
    const endDate = this.data.endDate;
    const deadline = this.data.deadline;
     // 确保所有数据都已经选择或填写
     if (!selectedSlot || !startDate || !endDate || !deadline) {
      wx.showToast({
        title: '请完整填写所有信息',
        icon: 'none'
      });
      return;
    }
 
      // 调用云函数添加记录
      wx.cloud.callFunction({
        name: 'addClock',
        data: {
          user_id,
          selectedSlot,
          startDate,
          endDate,
          deadline
        },
        success: res => {
          if (res.result.success) {
            wx.showToast({
              title: '打卡习惯添加成功',
            });
            // 添加成功后的处理，如返回上一页
            wx.navigateBack();
          } else {
            wx.showToast({
              title: '添加失败，请重试',
              icon: 'none'
            });
            console.error('云函数调用失败：', res.result.error);
          }
        },
        fail: err => {
          wx.showToast({
            title: '添加失败，请重试',
            icon: 'none'
          });
          console.error('云函数调用失败：', err);
        }
      });

    // 然后返回上一页
    wx.navigateBack({
      delta: 1 // 返回上一级页面
    });
  },

  cancelAction: function() {
    // 如果不需要执行额外操作，直接返回上一页
    wx.navigateBack({
      delta: 1 // 返回上一级页面
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