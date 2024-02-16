
// 获取应用实例
const app = getApp();
// pages/habit/habit.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    user_id:"",
    hab_name:"",
    dataList: [], // 这里是从数据库获取的数据列表
    showAddModal: false,
    showUpdateModal: false,
    showDeleteCheckbox: false,
    showQueryModal: false,
    currentHabit: {}, // 当前要编辑的习惯
  },

  // 显示添加习惯的弹窗
  showAddModal: function() {
    this.setData({ showAddModal: true });
  },
   // 隐藏添加习惯的弹窗
  hideAddModal: function() {
    this.setData({ showAddModal: false });
  },

   // 处理添加习惯
   handleAddHabit: function(e) {
     const that = this;
    // TODO: 发送请求到后端添加习惯
    console.log(e.detail.value.hab_name);
    const habit_name = e.detail.value.hab_name;
    wx.cloud.callFunction({
      name: 'addHabit',
      data: {
        hab_name: e.detail.value.hab_name,
        user_id: this.data.user_id // 通常这会是一个从小程序获取的用户唯一标识
      },
      success: function(res) {
        console.log('添加成功', res)
        that.updateHabitId(habit_name,that.data.user_id);
        that.showViewData();
      },
      fail: function(err) {
        console.error('添加失败', err)
      }
    });
    this.hideAddModal();
  },

  checkboxChange: function(e) {
    const habName = e.currentTarget.dataset.value; // 获取复选框对应的习惯名称
    const newDataList = this.data.dataList.map(item => {
      if (item.hab_name === habName) {
        item.checked = !item.checked; // 切换选中状态
      }
      return item;
    });
    this.setData({
      dataList: newDataList
    });
  },



// 显示删除复选框
showDeleteOptions: function() {
  this.setData({ showDeleteCheckbox: true });
},
// 确认删除所选习惯
confirmDelete: function() {
  const that = this;
  // TODO: 根据选中的checkbox值，发送请求到后端删除习惯
  let selectedHabits = this.data.dataList.filter(item => item.checked).map(item => item.hab_name);
  if (selectedHabits.length === 0) {
    wx.showToast({ title: '请选择要删除的习惯', icon: 'none' });
    return;
  }
    // 为每个选中的习惯调用删除云函数
    const batchPromise = selectedHabits.map(habit => {
      return wx.cloud.callFunction({
        name: 'deleteHabit',
        data: {
          user_id: that.data.user_id,
          hab_name: habit.hab_name // 现在使用习惯名作为删除条件
        }
      });
    });

    Promise.all(batchPromise).then(res => {
      wx.showToast({ title: '删除成功' });
      console.log('删除选中的习惯');
      this.showViewData(); // 重新加载数据
    }).catch(err => {
      wx.showToast({ title: '删除失败', icon: 'none' });
      console.error('删除失败', err);
    });

  this.setData({ showDeleteCheckbox: false });
},
// 显示修改习惯的弹窗
showUpdateModal: function() {
  this.setData({ showUpdateModal: true });
},
// 隐藏修改习惯的弹窗
hideUpdateModal: function() {
  this.setData({ showUpdateModal: false });
},
// 修改习惯
updateHabit: function() {
  // TODO: 发送请求到后端修改习惯
  const that = this;
  const { currentHabit } = this.data;
  if (!currentHabit.hab_name) {
    wx.showToast({ title: '信息不完整', icon: 'none' });
    return;
  }
  wx.cloud.callFunction({
    name: 'updateHabit',
    data: {
      user_id: that.data.user_id,
      old_hab_name: currentHabit.old_hab_name, // 原来的习惯名称
      new_hab_name: currentHabit.new_hab_name
    },
    success: res => {
      wx.showToast({ title: '更新成功' });
      that.showViewData(); // 重新加载数据
      that.setData({
        currentHabit: {} // 重置当前习惯
      });
    },
    fail: err => {
      wx.showToast({ title: '更新失败', icon: 'none' });
      console.error('更新失败', err);
    },
  });
  console.log('修改习惯', this.data.currentHabit);
  this.hideUpdateModal();
},
// 下拉选择器更改选项时触发
pickerChange: function(e) {
  const index = e.detail.value;
  const selectedHabit = this.data.dataList[index];
  this.setData({
    currentHabit: {
      ...selectedHabit,  // 复制选中的习惯所有信息
      old_hab_name: selectedHabit.hab_name, // 存储旧的习惯名称
      new_hab_name: selectedHabit.hab_name // 保持习惯名作为初始值
    }
  });
},
// 输入框内容变化时触发
inputChange: function(e) {
  this.setData({
    'currentHabit.new_hab_name': e.detail.value // 更新新的习惯名称
  });
},

// 显示删除复选框
  showDeleteOptions: function() {
    this.setData({ showDeleteCheckbox: true });
  },
  // 确认删除所选习惯
  confirmDelete: function() {
    // TODO: 根据选中的checkbox值，发送请求到后端删除习惯
    console.log('删除选中的习惯');
    this.setData({ showDeleteCheckbox: false });
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    this.findUserId();
    this.showViewData();
  },

  //初次加载页面数据
  showViewData(){
    const that = this;
  wx.cloud.callFunction({
    name: 'queryHabitsByUserId',
    data: {
      user_id: that.data.user_id
    },
    success: function(res) {
      if (res.result.code === 200) {
        that.setData({
          dataList: res.result.data
        });
        console.log("初次加载数据："+res.result.data)
      } else {
        console.log(res.result.message);
      }
    },
    fail: function(err) {
      console.error(err);
    }
  });
  },

 // 查询习惯的函数
 queryHabits: function() {
  const that = this;
  wx.cloud.callFunction({
    name: 'queryHabitsByUserId',
    data: {
      user_id: that.data.user_id
    },
    success: function(res) {
      if (res.result.code === 200) {
        that.setData({
          dataList: res.result.data
        });
        console.log(res.result.data)
      } else {
        console.log(res.result.message);
      }
    },
    fail: function(err) {
      console.error(err);
    }
  });
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

  findUserId(){
    wx.cloud.callFunction({
      name:'getOpenId'
    })
    .then(res => {
      console.log('成功',res.result.openid)
      
      this.setData({
        user_id: res.result.openid
      })
    })
    .catch(res=>{
      console.log('失败',res)
    })
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