// pages/per_info/per_info.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    user_id:"",
    user_name:"",
    user_image:"",
    user_phone:"",
    user_email:""
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
   
    this.setData({
      user_id: options.user_id,
      user_image: decodeURIComponent(options.user_image),
      user_name: decodeURIComponent(options.user_name),

    })
    if (this.data.user_id) {
      console.log("这是per_info启动页面"+this.data.user_id);
      this.getUserInfo(this.data.user_id);
    }
    console.log(this.data.user_id);
    //从数据库拿值
  },

  getUserInfo: function(user_id) {
    const that = this;
    wx.cloud.callFunction({
      name: 'getUserData',
      data: { user_id },
      success: res => {
        if (res.result.success) {
          // const { phone, email } = res.result.data;
          // console.log("res.result.data:"+res.result.data[0]);
          console.log("res.result.data.user_id:"+res.result.data[0].user_id);
         
          const phone = res.result.data[0].user_phone;
          const email = res.result.data[0].user_email;
          that.setData({
            user_phone: phone || '',
            user_email: email || '',
          });
          console.log("个人信息："+this.data.user_id);
          console.log("个人信息："+this.data.user_image);
          console.log("个人信息："+this.data.user_name);
          console.log("个人信息："+this.data.user_phone);
          console.log("个人信息："+this.data.user_email);
        } else {
          console.error('获取用户信息失败', res.result.error);
        }
      },
      fail: err => {
        console.error('调用云函数失败', err);
      }
    });
  },

  editPhone: function() {
    const that = this;
    wx.showModal({
      title: '编辑手机号',
      editable: true, // 允许输入内容
      placeholderText: '请输入手机号', // 提示信息
      success: function(res) {
        if (res.confirm && res.content) {
          that.setData({
            user_phone: res.content
          });
        }
      }
    });
  },

  // 编辑电子邮箱
  editEmail: function() {
    const that = this;
    wx.showModal({
      title: '编辑电子邮件',
      
      editable: true, // 允许输入内容
      placeholderText: '请输入电子邮箱', // 提示信息
      success: function(res) {
        if (res.confirm && res.content) {
          that.setData({
            user_email: res.content
          });
        }
      }
    });
  },

  saveUserInfo: function() {
    
    wx.cloud.callFunction({
      name: 'addUser',
      data: {
        user_id:this.data.user_id,
        user_name:this.data.user_name,
        user_image:this.data.user_image,
        user_phone: this.data.user_phone,
        user_email: this.data.user_email
      },
      success: res => {
        if (res.result.success) {
          wx.showToast({
            title: '保存成功',
            icon: 'success',
            duration: 2000
          });
        } else {
          console.error('保存失败', res.result.error);
          console.log(this.data.user_id);
          console.log(this.data.user_name);
          console.log(this.data.user_image);
          console.log(this.data.user_email);
          console.log(this.data.user_phone);
          wx.showToast({
            title: '保存失败',
            icon: 'none',
            duration: 2000
          });
        }
      },
      fail: err => {
        console.error('调用云函数失败', err);
        wx.showToast({
          title: '调用失败',
          icon: 'none',
          duration: 2000
        });
      }
    });

  },

  cancelEdit: function() {
    // 退回上一个页面
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