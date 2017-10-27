Git Workflow
=============================
[1 Git Feature Branch Workflow](#1)  
&emsp;&emsp;[1.1 How it works](#1.1)  
&emsp;&emsp;&emsp;&emsp;[1.1.1 Start with the master branch](#1.1.1)  
&emsp;&emsp;&emsp;&emsp;[1.1.2 Create a new-branch](#1.1.2)  
&emsp;&emsp;&emsp;&emsp;[1.1.3 Update, add, commit, and push changes](#1.1.3)  
&emsp;&emsp;&emsp;&emsp;[1.1.4 Push feature branch to remote](#1.1.4)  
&emsp;&emsp;&emsp;&emsp;[1.1.5 Resolve feedback](#1.1.5)  
&emsp;&emsp;&emsp;&emsp;[1.1.6 Merge your pull request](#1.1.6)  
&emsp;&emsp;[1.2 Pull requests](#1.2)  
&emsp;&emsp;[1.3 Example](#1.3)  
&emsp;&emsp;&emsp;&emsp;[1.3.1 Mary begins a new feature](#1.3.1)  
&emsp;&emsp;&emsp;&emsp;[1.3.2 Mary goes to lunch](#1.3.2)  
&emsp;&emsp;&emsp;&emsp;[1.3.3 Mary finishes her feature](#1.3.3)  
&emsp;&emsp;&emsp;&emsp;[1.3.4 Bill receives the pull request](#1.3.4)  
&emsp;&emsp;&emsp;&emsp;[1.3.5 Mary makes the changes](#1.3.5)  
&emsp;&emsp;&emsp;&emsp;[1.3.6 Mary publishes her feature](#1.3.6)  
&emsp;&emsp;&emsp;&emsp;[1.3.7 Meanwhile, John is doing the exact same thing](#1.3.7)  
[2 Gitflow Workflow](#2)  
&emsp;&emsp;[2.1 How it works](#2.1)  
&emsp;&emsp;&emsp;&emsp;[2.1.1 Develop and Master Branches](#2.1.1)  
&emsp;&emsp;[2.2 Feature Branches](#2.2)  
&emsp;&emsp;&emsp;&emsp;[2.2.1 Creating a feature branch](#2.2.1)  
&emsp;&emsp;&emsp;&emsp;[2.2.2 Finishing a feature branch](#2.2.2)  
&emsp;&emsp;[2.3 Release Branches](#2.3)  
&emsp;&emsp;[2.4 Example](#2.4)  
[3 Forking Workflow](#3)  
&emsp;&emsp;[3.1 How it works](#3.1)  
&emsp;&emsp;[3.2 Forking vs cloning](#3.2)  
&emsp;&emsp;[3.3 Branching in the Forking Workflow](#3.3)  
&emsp;&emsp;[3.4 Fork a repository](#3.4)  
&emsp;&emsp;[3.5 Clone your fork](#3.5)  
&emsp;&emsp;[3.6 Adding a remote](#3.6)  
&emsp;&emsp;[3.7 Working in a branch: making & pushing changes](#3.7)  
&emsp;&emsp;[3.8 Making a Pull Request](#3.8)  

------

<div id="1">

## Git Feature Branch Workflow

The core idea behind the Feature Branch Workflow is that all feature development should take place in a dedicated branch instead of the `master` branch. This encapsulation makes it easy for multiple developers to work on a particular feature without disturbing the main codebase. It also means the `master` branch will never contain broken code, which is a huge advantage for continuous integration environments.

Encapsulating feature development also makes it possible to leverage pull requests, which are a way to initiate discussions around a branch. They give other developers the opportunity to sign off on a feature before it gets integrated into the official project. Or, if you get stuck in the middle of a feature, you can open a pull request asking for suggestions from your colleagues. The point is, pull requests make it incredibly easy for your team to comment on each other’s work.

The Git Feature Branch Workflow is a composable workflow that can be leveraged by other high-level Git workflows. We discussed other Git workflows on the Git workflow overview page. Git Feature Branch Workflow is branching model focused, meaning that it is a guiding framework for managing and creating branches. Other workflows are more repo focused. The Git Feature Branch Workflow can be incorporated into other workflows. The Gitflow, and Git Forking Workflows traditionally use a Git Feature Branch Workflow in regards to their branching models.

<div id="1.1">

------

### How it works

The Feature Branch Workflow assumes a central repository, and `master` represents the official project history. Instead of committing directly on their local `master` branch, developers create a new branch every time they start work on a new feature. Feature branches should have descriptive names, like animated-menu-items or issue-#1061. The idea is to give a clear, highly-focused purpose to each branch. Git makes no technical distinction between the `master` branch and feature branches, so developers can edit, stage, and commit changes to a feature branch.
 
In addition, feature branches can (and should) be pushed to the central repository. This makes it possible to share a feature with other developers without touching any official code. Since `master` is the only “special” branch, storing several feature branches on the central repository doesn’t pose any problems. Of course, this is also a convenient way to back up everybody’s local commits. The following is a walk-through of the life-cycle of a feature branch.

<div id="1.1.1">

#### Start with the master branch

All feature branches are created off the latest code state of a project. This guide assumes this is maintained and updated in the `master` branch.  
```
git checkout master
git fetch origin
git reset --hard origin/master
```
This switches the repo to the `master` branch, pulls the latest commits and resets the repo's local copy of `master` to match the latest version.

<div id="1.1.2">

#### Create a new-branch

Use a separate branch for each feature or issue you work on. After creating a branch, check it out locally so that any changes you make will be on that branch.  
```
git checkout -b new-feature
```  
This checks out a branch called new-feature based on `master`, and the -b flag tells Git to create the branch if it doesn’t already exist.

<div id="1.1.3">

#### Update, add, commit, and push changes

On this branch, edit, stage, and commit changes in the usual fashion, building up the feature with as many commits as necessary. Work on the feature and make commits like you would any time you use Git. When ready, push your commits, updating the feature branch on Bitbucket.  
```
git status
git add <some-file>
git commit
```

<div id="1.1.4">

#### Push feature branch to remote

It’s a good idea to push the feature branch up to the central repository. This serves as a convenient backup, when collaborating with other developers, this would give them access to view commits to the new branch.  
```
git push -u origin new-feature
```  
This command pushes new-feature to the central repository (origin), and the -u flag adds it as a remote tracking branch. After setting up the tracking branch, git push can be invoked without any parameters to automatically push the new-feature branch to the central repository. To get feedback on the new feature branch, create a pull request in a repository management solution like Bitbucket Cloud or Bitbucket Server. From there, you can add reviewers and make sure everything is good to go before merging.

<div id="1.1.5">

#### Resolve feedback

Now teammates comment and approve the pushed commits. Resolve their comments locally, commit, and push the suggested changes to Bitbucket. Your updates appear in the pull request.

<div id="1.1.6">

#### Merge your pull request

Before you merge, you may have to resolve merge conflicts if others have made changes to the repo. When your pull request is approved and conflict-free, you can add your code to the `master` branch. Merge from the pull request in Bitbucket.

------

<div id="1.2">

### Pull requests

Aside from isolating feature development, branches make it possible to discuss changes via pull requests. Once someone completes a feature, they don’t immediately merge it into `master`. Instead, they push the feature branch to the central server and file a pull request asking to merge their additions into `master`. This gives other developers an opportunity to review the changes before they become a part of the main codebase.

Code review is a major benefit of pull requests, but they’re actually designed to be a generic way to talk about code. You can think of pull requests as a discussion dedicated to a particular branch. This means that they can also be used much earlier in the development process. For example, if a developer needs help with a particular feature, all they have to do is file a pull request. Interested parties will be notified automatically, and they’ll be able to see the question right next to the relevant commits.

Once a pull request is accepted, the actual act of publishing a feature is much the same as in the Centralized Workflow. First, you need to make sure your local `master` is synchronized with the upstream `master`. Then, you merge the feature branch into `master` and push the updated `master` back to the central repository.

Pull requests can be facilitated by product repository management solutions like Bitbucket Cloud or Bitbucket Server. View the Bitbucket Server pull requests documentation for an example.

------

<div id="1.3">

### Example

The following is an example of the type of scenario in which a feature branching workflow is used. The scenario is that of a team doing code review around on a new feature pull request. This is one example of the many purposes this model can be used for.

<div id="1.3.1">

#### Mary begins a new feature

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/02.jpg)
Before she starts developing a feature, Mary needs an isolated branch to work on. She can request a new branch with the following command:
```
git checkout -b marys-feature master
```   
This checks out a branch called marys-feature based on `master`, and the -b flag tells Git to create the branch if it doesn’t already exist. On this branch, Mary edits, stages, and commits changes in the usual fashion, building up her feature with as many commits as necessary:
```
git status
git add <some-file>
git commit
```

<div id="1.3.2">

#### Mary goes to lunch

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/03.jpg)
Mary adds a few commits to her feature over the course of the morning. Before she leaves for lunch, it’s a good idea to push her feature branch up to the central repository. This serves as a convenient backup, but if Mary was collaborating with other developers, this would also give them access to her initial commits.
```
git push -u origin marys-feature
```  
This command pushes marys-feature to the central repository (origin), and the -u flag adds it as a remote tracking branch. After setting up the tracking branch, Mary can call git push without any parameters to push her feature.

<div id="1.3.3">

#### Mary finishes her feature

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/04.jpg)
When Mary gets back from lunch, she completes her feature. Before merging it into `master`, she needs to file a pull request letting the rest of the team know she's done. But first, she should make sure the central repository has her most recent commits:
```
git push
```  
Then, she files the pull request in her Git GUI asking to merge marys-feature into `master`, and team members will be notified automatically. The great thing about pull requests is that they show comments right next to their related commits, so it's easy to ask questions about specific changesets.

<div id="1.3.4">

#### Bill receives the pull request

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/05.jpg)
Bill gets the pull request and takes a look at marys-feature. He decides he wants to make a few changes before integrating it into the official project, and he and Mary have some back-and-forth via the pull request.

<div id="1.3.5">

#### Mary makes the changes

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/06.jpg)
To make the changes, Mary uses the exact same process as she did to create the first iteration of her feature. She edits, stages, commits, and pushes updates to the central repository. All her activity shows up in the pull request, and Bill can still make comments along the way.

If he wanted, Bill could pull marys-feature into his local repository and work on it on his own. Any commits he added would also show up in the pull request.

<div id="1.3.6">

#### Mary publishes her feature

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/07.jpg)
Once Bill is ready to accept the pull request, someone needs to merge the feature into the stable project (this can be done by either Bill or Mary):
```
git checkout master
git pull
git pull origin marys-feature
git push
```
This process often results in a merge commit. Some developers like this because it’s like a symbolic joining of the feature with the rest of the code base. But, if you’re partial to a linear history, it’s possible to rebase the feature onto the tip of `master` before executing the merge, resulting in a fast-forward merge.

Some GUI’s will automate the pull request acceptance process by running all of these commands just by clicking an “Accept” button. If yours doesn’t, it should at least be able to automatically close the pull request when the feature branch gets merged into `master`.

<div id="1.3.7">

#### Meanwhile, John is doing the exact same thing

While Mary and Bill are working on marys-feature and discussing it in her pull request, John is doing the exact same thing with his own feature branch. By isolating features into separate branches, everybody can work independently, yet it’s still trivial to share changes with other developers when necessary.

<div id="2">

## Gitflow Workflow

Gitflow Workflow is a Git workflow design that was first published and made popular by Vincent Driessen at nvie. The Gitflow Workflow defines a strict branching model designed around the project release. This provides a robust framework for managing larger projects.  

Gitflow is ideally suited for projects that have a scheduled release cycle. This workflow doesn’t add any new concepts or commands beyond what’s required for the Feature Branch Workflow. Instead, it assigns very specific roles to different branches and defines how and when they should interact. In addition to feature branches, it uses individual branches for preparing, maintaining, and recording releases. Of course, you also get to leverage all the benefits of the Feature Branch Workflow: pull requests, isolated experiments, and more efficient collaboration.

In addition to the abstract Gitflow Workflow idea, there is a more tangible git-flow toolset available which integrates with Git to provide specialized Gitflow Git command line tool extensions.

------

<div id="2.1">

### How it works

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/02%20(2).jpg)

<div id="2.1.1">

#### Develop and Master Branches

Instead of a single `master` branch, this workflow uses two branches to record the history of the project. The `master` branch stores the official release history, and the develop branch serves as an integration branch for features. It's also convenient to tag all commits in the `master` branch with a version number.

The first step is to complement the default `master` with a develop branch. A simple way to do this is for one developer to create an empty develop branch locally and push it to the server:
```
git branch develop
git push -u origin develop
```
This branch will contain the complete history of the project, whereas `master` will contain an abridged version. Other developers should now clone the central repository and create a tracking branch for develop.

------

<div id="2.2">

### Feature Branches

Each new feature should reside in its own branch, which can be pushed to the central repository for backup/collaboration. But, instead of branching off of `master`, feature branches use develop as their parent branch. When a feature is complete, it gets merged back into develop. Features should never interact directly with `master`.

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/03%20(2).jpg)
Note that feature branches combined with the develop branch is, for all intents and purposes, the Feature Branch Workflow. But, the Gitflow Workflow doesn’t stop there.

Feature branches are generally created off to the latest develop branch.

<div id="2.2.1">

#### Creating a feature branch

```
git checkout develop
git checkout -b feature_branch
```
Continue your work and use Git like you normally would.

<div id="2.2.2">

#### Finishing a feature branch
 
When you’re done with the development work on the feature, the next step is to merge the feature_branch into develop.

```
git checkout develop
git merge feature_branch
```

------

<div id="2.3">

### Release Branches

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/04%20(2).jpg)

Once develop has acquired enough features for a release (or a predetermined release date is approaching), you fork a release branch off of develop. Creating this branch starts the next release cycle, so no new features can be added after this point—only bug fixes, documentation generation, and other release-oriented tasks should go in this branch. Once it's ready to ship, the release branch gets merged into `master` and tagged with a version number. In addition, it should be merged back into develop, which may have progressed since the release was initiated.

Using a dedicated branch to prepare releases makes it possible for one team to polish the current release while another team continues working on features for the next release. It also creates well-defined phases of development (e.g., it's easy to say, “This week we're preparing for version 4.0,” and to actually see it in the structure of the repository).

Making release branches is another straightforward branching operation. Like feature branches, release branches are based on the develop branch. A new release branch can be created using the following methods.

```
git checkout develop
git checkout -b release/0.1.0
```
Once the release is ready to ship, it will get merged it into `master` and develop, then the release branch will be deleted. It’s important to merge back into develop because critical updates may have been added to the release branch and they need to be accessible to new features. If your organization stresses code review, this would be an ideal place for a pull request.

To finish a release branch, use the following methods:

```
git checkout develop
git merge release/0.1.0
```

------

<div id="2.4">

### Example

A complete example demonstrating a Feature Branch Flow is as follows. Assuming we have a repo setup with a `master` branch.

```
git checkout -b develop
git checkout -b release/0.1.0
git checkout develop
git checkout -b feature_branch
# a bunch of work is done on the features
git checkout release/0.1.0
git merge feature_branch
# assuming that the release branch is done with that feature
git checkout develop
git merge release/0.1.0
git checkout master
git merge release/0.1.0
git branch -D release/0.1.0
```

------

<div id="3">

# Forking Workflow
 

The Forking Workflow is fundamentally different than other popular Git workflows. Instead of using a single server-side repository to act as the “central” codebase, it gives every developer their own server-side repository. This means that each contributor has not one, but two Git repositories: a private local one and a public server-side one. The Forking Workflow is most often seen in public open source projects.

The main advantage of the Forking Workflow is that contributions can be integrated without the need for everybody to push to a single central repository. Developers push to their own server-side repositories, and only the project maintainer can push to the official repository. This allows the maintainer to accept commits from any developer without giving them write access to the official codebase.

The Forking Workflow typically follows a branching model based on the Gitflow Workflow. This means that complete feature branches will be purposed for merge into the original project maintainer's repository. The result is a distributed workflow that provides a flexible way for large, organic teams (including untrusted third-parties) to collaborate securely. This also makes it an ideal workflow for open source projects.
 
 ------
 
<div id="3.1">

### How it works

As in the other Git workflows, the Forking Workflow begins with an official public repository stored on a server. But when a new developer wants to start working on the project, they do not directly clone the official repository.

Instead, they fork the official repository to create a copy of it on the server. This new copy serves as their personal public repository—no other developers are allowed to push to it, but they can pull changes from it (we’ll see why this is important in a moment). After they have created their server-side copy, the developer performs a git clone to get a copy of it onto their local machine. This serves as their private development environment, just like in the other workflows.

When they're ready to publish a local commit, they push the commit to their own public repository—not the official one. Then, they file a pull request with the main repository, which lets the project maintainer know that an update is ready to be integrated. The pull request also serves as a convenient discussion thread if there are issues with the contributed code. The following is a step-by-step example of this workflow.

 

1. A developer 'forks' an 'official' server-side repository. This creates their own server-side copy.
2. The new server-side copy is cloned to their local system.
3. A Git remote path for the 'official' repository is added to the local clone.
4. A new local feature branch is created.
5. The developer makes changes on the new branch.
6. New commits are created for the changes.
7. The branch gets pushed to the developer's own server-side copy.
8. The developer opens a pull request from the new branch to the 'official' repository.
9. The pull request gets approved for merge and is merged into the original server-side repository
 
To integrate the feature into the official codebase, the maintainer pulls the contributor’s changes into their local repository, checks to make sure it doesn’t break the project, merges it into his local `master` branch, then pushes the `master` branch to the official repository on the server. The contribution is now part of the project, and other developers should pull from the official repository to synchronize their local repositories.

It’s important to understand that the notion of an “official” repository in the Forking Workflow is merely a convention. In fact, the only thing that makes the official repository so official is that it’s the public repository of the project maintainer.

------

<div id="3.2">

### Forking vs cloning

It's important to note that "forked" repositories and "forking" are not special operations. Forked repositories are created using the standard git clone command. Forked repositories are generally "server-side clones" and usually managed and hosted by a 3rd party Git service like Bitbucket. There is no unique Git command to create forked repositories. A clone operation is essentially a copy of a repository and its history. 

------

<div id="3.3">

### Branching in the Forking Workflow

All of these personal public repositories are really just a convenient way to share branches with other developers. Everybody should still be using branches to isolate individual features, just like in the Feature Branch Workflow and the Gitflow Workflow. The only difference is how those branches get shared. In the Forking Workflow, they are pulled into another developer’s local repository, while in the Feature Branch and Gitflow Workflows they are pushed to the official repository.

------

<div id="3.4">

### Fork a repository

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/03%20(3).jpg)
All new developers to a Forking Workflow project need to fork the official repository. As previously stated, forking is just a standard git clone operation. It’s possible to do this by SSH’ing into the server and running git clone to copy it to another location on the server. Popular Git hosting services like Bitbucket, offer repo forking features that automate this step.

------

<div id="3.5">

### Clone your fork

Next each developer needs to clone their own public forked repository. They can do this with the familiar git clone command.

Assuming the use of Bitbucket to host these repositories, developers on a project should have their own Bitbucket account and they should clone their forked copy of the repository with:  
```
git clone https://user@bitbucket.org/user/repo.git
```  

------

<div id="3.6">

### Adding a remote

Whereas other Git workflows use a single origin remote that points to the central repository, the Forking Workflow requires two remotes—one for the official repository, and one for the developer’s personal server-side repository. While you can call these remotes anything you want, a common convention is to use origin as the remote for your forked repository (this will be created automatically when you run git clone) and upstream for the official repository.  
```
git remote add upstream https://bitbucket.org/maintainer/repo
```  
You’ll need to create the upstream remote yourself using the above command. This will let you easily keep your local repository up-to-date as the official project progresses. Note that if your upstream repository has authentication enabled (i.e., it's not open source), you'll need to supply a username, like so:  
```
git remote add upstream https://user@bitbucket.org/maintainer/repo.git
```  
This requires users to supply a valid password before cloning or pulling from the official codebase.

------

<div id="3.7">

### Working in a branch: making & pushing changes

In the developer's local copy of the forked repository they can edit code, commit changes, and create branches just like in other Git workflows:
```
git checkout -b some-feature
# Edit some code
git commit -a -m "Add first draft of some feature"
```
All of their changes will be entirely private until they push it to their public repository. And, if the official project has moved forward, they can access new commits with git pull:
```
git pull upstream master
```
Since developers should be working in a dedicated feature branch, this should generally result in a fast-forward merge.

------

<div id="3.8">

### Making a Pull Request

![](https://github.com/WhirlFourEye/MyProject/blob/master/static/05%20(3).jpg)
Once a developer is ready to share their new feature, they need to do two things. First, they have to make their contribution accessible to other developers by pushing it to their public repository. Their origin remote should already be set up, so all they should have to do is the following:
```
git push origin feature-branch
```
This diverges from the other workflows in that the origin remote points to the developer’s personal server-side repository, not the main codebase.

Second, they need to notify the project maintainer that they want to merge their feature into the official codebase. Bitbucket provides a “pull request” button that leads to a form asking you to specify which branch you want to merge into the official repository. Typically, you’ll want to integrate your feature branch into the upstream remote’s `master` branch.
