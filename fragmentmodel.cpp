#include "fragmentmodel.h"

FragmentModel::FragmentModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    fragments.append(FragmentInfo(64, "434D", QTime(0,3,4,0), "добвлено"));
    fragments.append(FragmentInfo(43, "423r", QTime(0,33,4,0), "добвлено"));
    fragments.append(FragmentInfo(12, "4T", QTime(0,3,34,0), "добвлено"));
    fragments.append(FragmentInfo(FrameRange(32, 214), PillarRange("5", "23d"), TimeRange(QTime(0,3,4,0), QTime(0,4,4,0)), "Добавленно"));
}

QVariant FragmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers.at(section);
    else
        return QVariant();
}

int FragmentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return fragments.count();
}

int FragmentModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();
}

QVariant FragmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::CheckStateRole && index.column() == 0){
        if (std::find(ss.begin(), ss.end(), &fragments[index.row()]) != ss.end()){
            return Qt::Checked;
        }else {
            return Qt::Unchecked;
        }
    }
    if (role == Qt::DisplayRole){
        switch (index.column()) {
        case 1:
            return fragments.at(index.row()).getStatus();
        case 2:
            if (fragments.at(index.row()).isVideoFragment()){
                auto result = QString("%1 - %2")
                                .arg(fragments.at(index.row()).getFrameRange().first)
                                .arg(fragments.at(index.row()).getFrameRange().second);
                return result;
            } else {
                return fragments.at(index.row()).getFrameRange().first;
            }
        case 3:
            if (fragments.at(index.row()).isVideoFragment()){
                auto result = QString("%1 - %2")
                                .arg(fragments.at(index.row()).getPillarRange().first)
                                .arg(fragments.at(index.row()).getPillarRange().second);
                return result;
            } else {
                return fragments.at(index.row()).getPillarRange().first;
            }
        case 4:
            if (fragments.at(index.row()).isVideoFragment()){
                auto result = QString("%1 - %2")
                                .arg(fragments.at(index.row()).getTime().first.toString("hh:mm:ss"))
                                .arg(fragments.at(index.row()).getTime().second.toString("hh:mm:ss"));
                return result;
            } else {
                return fragments.at(index.row()).getTime().first.toString("hh:mm:ss");
            }
        case 5:
            return fragments.at(index.row()).getFrameNumberReport();
        }
    }
    return QVariant();

}

bool FragmentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::CheckStateRole)
    {
        if (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked)
        {
//            selectedFraments.append(&fragments[index.row()]);
                ss.push_back(fragments[index.row()]);

            return true;
        }
        else
        {
//            if (selectedFraments.contains(&fragments[index.row()])){
//                selectedFraments.removeOne(&fragments[index.row()]);
//            }
            return true;
        }
    }
    return false;
}

Qt::ItemFlags FragmentModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEditable |Qt::ItemIsEnabled;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void FragmentModel::addFragment(const FragmentInfo &fragment)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    fragments.append(fragment);
    endInsertRows();
}

void FragmentModel::removeFragment(const QModelIndexList modelIdexesList)
{
    if (fragments.isEmpty() || modelIdexesList.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), modelIdexesList.first().row(), modelIdexesList.last().row());
    for (const auto &modelIndex : modelIdexesList){
        fragments.removeAt(modelIndex.row());
    }
    endRemoveRows();
}

void FragmentModel::clearModel()
{
    while (!fragments.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, 0);
        fragments.removeFirst();
        endRemoveRows();
    }
}


//TODO: Я думаю можно лучше сделать
QList<FragmentInfo> FragmentModel::getFragments(FiltersFlags filters) const
{
//    QList<FragmentInfo> resultFragmets;
//    if (filters.testFlag(AllFragments)){
//        for (auto &fragment : fragments) {
//            resultFragmets.append(fragment.info);
//        }
//    } else if (filters.testFlag(VideoFragments)) {
//        for (auto fragment : fragments)
//            if (fragment.info.isVideoFragment())
//                resultFragmets.append(fragment.info);
//    }else if (filters.testFlag(FrameFragments)) {
//        for (auto fragment : fragments)
//            if (!fragment.info.isVideoFragment())
//                resultFragmets.append(fragment.info);
//    }
}

bool FragmentModel::isContainsVideoFragment()
{
    for (auto &fragment : fragments) {
        if (fragment.isVideoFragment())
            return true;
    }
    return false;
}

bool FragmentModel::isEmpty()
{
    return fragments.isEmpty();
}
