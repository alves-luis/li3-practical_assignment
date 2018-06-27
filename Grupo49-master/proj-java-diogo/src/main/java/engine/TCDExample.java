package engine;

import common.Pair;
import common.Post;
import common.User;
import common.Tag;
import li3.TADCommunity;
import engine.Comparator.*;
import engine.Parser.*;
import engine.Exception.*;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;


/**
 * Engine of the program
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

public class TCDExample implements TADCommunity {

    private Map<Long, Post> posts;
    private Map<Long, User> users;
    private Map<String, Tag> tags;
    private Set<Post> setTempo;


    public TCDExample(){
        this.posts = new HashMap<>();
        this.users = new HashMap<>();
        this.tags  = new HashMap<>();
        this.setTempo = new TreeSet<>(new ComparatorData());
    }

    public void load(String dumpPath) {
        String user_path = dumpPath + "Users.xml";
        String post_path = dumpPath + "Posts.xml";
        String tag_path = dumpPath + "Tags.xml";

        ParserUsers user_file = new ParserUsers(user_path);
        this.users = user_file.getUsers();

        ParserPosts post_file = new ParserPosts(post_path);
        this.posts = post_file.getPosts();
        this.setTempo = post_file.getSetPosts();

        ParserTags tag_file = new ParserTags(tag_path);
        this.tags = tag_file.getTags();

        this.posts.values().forEach(p -> this.users.get(p.getUserId()).incPostC());
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        try{
            if(!this.posts.containsKey(id)) throw new InvalidIdException("User Inexistente!");
            Post x = this.posts.get(id);
            User y = this.users.get(x.getUserId());
            // 1 is a question;
            if (x.getPostType() == 1)
                return new Pair<>(x.getTitle(), y.getNickname());
            else{
                Post question = this.posts.get(x.getParentId());
                y = this.users.get(question.getUserId());
                return new Pair<>(question.getTitle(), y.getNickname());
            }
        }
        catch(InvalidIdException e){
            e.message();
        }
        return new Pair<>(null,null);
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return  this.users.values().stream()
                .map(p -> p.clone())
                .sorted(new ComparatorUserCount())
                .map(e -> e.getId())
                .limit(N)
                .collect(Collectors.toList());
    }


    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {

        return new Pair<>(this.setTempo.stream().filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end)))).filter(e -> e.getPostType() == 1).count() ,
                          this.setTempo.stream().filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end)))).filter(e -> e.getPostType() == 2).count());
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return this.setTempo.stream()
                .filter(e -> e.getPostType() == 1)
                .filter(e -> e.getTags().contains(tag))
                .filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end))))
                .map(e -> e.getId())
                .collect(Collectors.toList());
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        try{
            if(!this.posts.containsKey(id)) throw new InvalidIdException("User Inexistente!");
            return new Pair<>(this.users.get(id).getShortBio(),
                    this.setTempo.stream()
                            .filter(p -> (p.getUserId() == id))
                            .map(p -> p.getId())
                            .limit(10)
                            .collect(Collectors.toList()));
        }
        catch(InvalidIdException e){
            e.message();
        }
        return new Pair<>(null,null);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return this.setTempo.stream()
                .filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end))))
                .filter(e -> (e.getPostType() == 2))
                .sorted(new ComparatorScore())
                .map(e -> e.getId())
                .limit(N)
                .collect(Collectors.toList());
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return this.setTempo.stream()
                .filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end))))
                .filter(e -> (e.getPostType() == 1))
                .sorted(new ComparatorAnswerCount())
                .map(e -> e.getId())
                .limit(N)
                .collect(Collectors.toList());
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return this.setTempo.stream()
                .filter(e -> (e.getPostType() == 1))
                .filter(e -> e.getTitle().contains(word))
                .map(e -> e.getId())
                .limit(N)
                .collect(Collectors.toList());
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        try{
            if (!(this.users.containsKey(id1) && this.users.containsKey(id2))) throw new InvalidIdException("User Inexistente!");
            List<Long> my_id_1 = getQuestion(id2);
            List<Long> my_id_2 = getQuestion(id1);

            List<Long> myList = new ArrayList<>();

            for (Long e : my_id_1){
                if (my_id_2.contains(e)) myList.add(e);
            }
            return myList.stream()
                    .distinct()
                    .collect(Collectors.toList());

        }
        catch(InvalidIdException e) {
            e.message();
        }
        return null;
    }

    public List<Long> getQuestion(long id){
        return this.setTempo.stream()
                .filter(p -> p.getUserId() == id)
                .map(p -> {
                    if (p.getPostType() == 2) {
                        return p.getParentId();
                    } else{
                        return p.getId();
                    }
                })
                .collect(Collectors.toList());
    }


    public Post calculateAnswer(Post p){
        p.setBestScore(p.getScore() * 0.65 + this.users.get(p.getUserId()).getRep() * 0.25 + p.getReply_number() * 0.1);
        return p;
    }

    // Query 10
    public long betterAnswer(long id) {
        try{
            if (!this.posts.containsKey(id)) throw new InvalidIdException("Post Inexistente!");
            return this.setTempo.stream()
                    .filter(p -> p.getParentId() == id)
                    .map(p -> p.clone())
                    .map(p -> calculateAnswer(p))
                    .sorted(new ComparatorBestAnswer())
                    .map(p -> p.getId())
                    .collect(Collectors.toList())
                    .get(0);
        }
        catch(InvalidIdException e) {
            e.message();
        }
        return -1;
    }

    // Query 11

    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {

        Map<String, Tag> tag_query = new HashMap<>();

        List<Long> myList = getTopUsers(N ,begin , end);
        List<String> myStringTag = getPostWithTags(myList , begin , end);

        StringBuilder all_tags_string = new StringBuilder();

        for (String e : myStringTag)
            all_tags_string.append(e);


        List <String> all_tags = SplitString(all_tags_string.toString());

        all_tags.forEach(p -> {
            if(this.tags.get(p) != null)
                if (tag_query.get(p) == null)
                    tag_query.put(p, this.tags.get(p).clone());
                tag_query.get(p).incCount();

        });

        return  tag_query.values()
                .stream()
                .sorted(new ComparatorCount())
                .map(e -> e.getId())
                .limit(N)
                .collect(Collectors.toList());
    }
    /**
     * This splits a string into a list of string taking out the < > of the tag
     * @param N the number of users
     * @param begin The begining of the period to be examed
     * @param end The end of the period to be examed
     * @return List<String> A list with all the tags from questions that the users asked
     */
    public List<Long> getTopUsers(int N, LocalDate begin, LocalDate end){
        return this.setTempo.stream()
                .filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end))))
                .map(p -> p.getUserId())
                .map(u -> this.users.get(u))
                .distinct()
                .sorted(new ComparatorTopUser())
                .limit(N)
                .map(u -> u.getId())
                .collect(Collectors.toList());
    }
    /**
     * This get all the tags from the top N users.
     * @param myList A list with all the Users
     * @return List<String> A list with all the tags from questions that the users asked
     */
    public List<String> getPostWithTags(List <Long> myList , LocalDate begin, LocalDate end){
        return this.setTempo.stream()
                .filter(e -> ((e.getDate().isAfter(begin) || e.getDate().equals(begin)) && (e.getDate().isBefore(end) || e.getDate().equals(end))))
                .filter(e -> e.getPostType() == 1)
                .filter(e -> myList.contains(e.getUserId()))
                .map(e -> e.getTags())
                .collect(Collectors.toList());
    }
    /**
     * This splits a string into a list of string taking out the < > of the tag
     * @param s string to be splitted
     * @return List<String> A list with all the tags
     */
    public List<String> SplitString(String s) {
        List <String> list = new ArrayList<>();
        String[] name = s.split(">"); // comma and space

        for (String p : name)
            list.add(p.replace("<", ""));

        return list;
    }

    public void clear(){
        this.users = null;
        this.tags = null;
        this.posts = null;
        this.setTempo = null;
    }
}
