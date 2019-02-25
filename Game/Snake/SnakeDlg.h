#ifndef SNAKEDLG_H
#define SNAKEDLG_H

#include <QDialog>
#include <QImage>
#include <QList>
#include <QLabel>
#include <QTimer>

namespace Ui {
class SnakeDlg;
}

class SnakeDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SnakeDlg(QWidget *parent = 0);
    ~SnakeDlg();

private:
    // 显示事件处理
    void showEvent (QShowEvent*);
    // 绘制事件处理
    void paintEvent (QPaintEvent*);
    // 键盘事件处理
    void keyPressEvent (QKeyEvent* event);

    // 初始化游戏
    void initGame (void);
    // 制造食物
    QLabel* makeFood (int x = -1, int y = -1);
    // 生成给定值域内的随机数
    int rand (int x, int y);
    // 对齐圆整
    // 返回小于x的最大的y的整数倍
    int round (int x, int y);
    // 计算下一步
    bool nextStep (QPoint& ptStep) const;
    // 判断有效位置
    bool validPos (QPoint const& ptPos) const;
    // 更新记分板
    void updateSb (void) const;

private slots:
    // 爬行定时器到期槽
    void crawlExpired (void);

private:
    Ui::SnakeDlg *ui;

    // 方向
    typedef enum tag_Direction {
        EDIR_UP,   // 向上
        EDIR_DOWN, // 向下
        EDIR_LEFT, // 向左
        EDIR_RIGHT // 向右
    }   EDIR;

    QImage           m_imgAction;  // 活动区图片
    QList<QLabel*>   m_lstSnake;   // 蛇节点链表
    QLabel*          m_labFood;    // 食物
    EDIR             m_eDir;       // 行进方向
    static const int s_nStep = 20; // 步距
    QTimer           m_tmrCrawl;   // 爬行定时器
    unsigned int     m_uScore;     // 得分
};

#endif // SNAKEDLG_H
